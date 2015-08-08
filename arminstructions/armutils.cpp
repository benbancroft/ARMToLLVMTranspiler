#include "armutils.h"

namespace Arm{

    ArmInstruction* ReadInstruction(std::ifstream* file, Elf::Endianness endianness, Elf::ELFHeader* header){
        //check if AArch64 uses 64-bit instructions?

        uint32_t rawInstruction = readInt32(file, endianness, header->endianness);

        auto bitset = Utils::IntegerToBitset(rawInstruction);

        Condition condition = static_cast<Condition>(rawInstruction >> 28);
        uint8_t baseType = static_cast<uint8_t>(rawInstruction >> 26 & 0b00000011);

        switch (baseType){
            case 0:
            {
                if (bitset[25] == 1 || bitset[7] == 0){
                    auto mnemonic = static_cast<DataProcessingInstructionTypes>(rawInstruction >> 21 & 0b00001111);
                    return new DataProcessingInstruction(condition, bitset[25], mnemonic);
                }else{
                    //type = InstructionType::Multiply;
                }
            }break;
        case 1:
        {
            if (bitset[25] == 1 && bitset[4] == 1){
                //InstructionType::Undefined;
                return NULL;
            }else{
                Register baseRegister = static_cast<Register>(rawInstruction >> 16 & 0b00001111);
                Register srcDestRegister = static_cast<Register>(rawInstruction >> 12 & 0b00001111);
                uint16_t offset = rawInstruction & 0b0000111111111111;
                return new SingleDataTransferInstruction(condition, !bitset[25], bitset[24], bitset[23], bitset[22], bitset[21], bitset[20], baseRegister, srcDestRegister, offset);
            }
        }break;
        case 2:
        {
            if (bitset[25] == 0){
                return new BlockDataTransferInstruction(condition);
            }else{
                int32_t addressoffset = (rawInstruction & 0x00FFFFFF) << 2;
                //sign extend twos compliment
                if (0x02000000 & addressoffset){
                    addressoffset |= 0xFF000000;
                }
                //"The  branch offset must take account of the prefetch operation, which causes the  PC  to be 2 words (8 bytes) ahead of the current instruction."
                return new BranchInstruction(condition, bitset[24], addressoffset);
            }
        }break;
        }


        return NULL;
    }

    BasicBlock* HandleInstruction(ProgramData* programData, Elf::Endianness systemEndianness, std::ifstream* binary, Elf::ELFHeader* header){
        ArmInstruction* inst = NULL;
        BasicBlock* block = new BasicBlock(programData->position);
        do {
            inst = Arm::ReadInstruction(binary, systemEndianness, header);

            block->blocks.push_back(inst);

            switch (inst->GetType()){
                case InstructionType::DataProcessing:
                {
                    auto dataProcessingInst = static_cast<DataProcessingInstruction*>(inst);
                    auto test = dataProcessingInst;
                }break;
                case InstructionType::Branch:
                {
                    auto branchInst = static_cast<BranchInstruction*>(inst);

                    //programData->position += 4;
                    //should happen every time, but stop at branch for debug
                    //if (inst->GetCondition() != Condition::AL){
                        //auto reference = HandleInstruction(programData, systemEndianness, binary, header);
                    //}
                    if (!branchInst->IsLinkedBranch()){
                        //account for branch pre?
                        int oldPos = programData->position;

                        programData->position = oldPos + 8 + branchInst->GetAddressOffset();
                        binary->seekg(programData->position);
                        auto reference = HandleInstruction(programData, systemEndianness, binary, header);

                        programData->position = oldPos;
                        binary->seekg(programData->position+4);
                    }
                    //break out of block
                }break;
            case InstructionType::SingleDataTransfer:
            {
                auto dataTransferInst = static_cast<SingleDataTransferInstruction*>(inst);
                dataTransferInst->GetCondition();

                if (dataTransferInst->getBaseRegister() == Register::PC && dataTransferInst->isStoreOrLoadTransfer() && dataTransferInst->isPostOrPreIndexing() && dataTransferInst->isImmediateOffset()){
                    // + 8 to account for branch pre
                    uint32_t dataPos = programData->position + 8 + (dataTransferInst->isDownUpOffset() ? 1 : -1) * dataTransferInst->getOffset();
                    binary->seekg(dataPos);

                    //Flag position as data
                    programData->dataAddresses.insert(dataPos);

                    if (!dataTransferInst->isByteOrWord()){
                        int32_t address = Elf::readInt32(binary, systemEndianness, header->endianness);
                        auto filePosition = Elf::mapVirtualAddressToFile(address, header);

                        int oldPos = programData->position;
                        binary->seekg(filePosition);

                        auto reference = HandleInstruction(programData, systemEndianness, binary, header);

                        programData->position = oldPos;
                        binary->seekg(programData->position+4);
                    }else{
                        //handle words
                    }
                    binary->seekg(programData->position+4);
                }
            }break;
            }

            programData->position += 4;
            //change to ordered binary search in future?
        } while(inst != NULL && programData->dataAddresses.find(programData->position) == programData->dataAddresses.end() && !std::any_of(programData->blocks.begin(), programData->blocks.end(), [programData](BasicBlock* b) { return b->GetStartAddress() == programData->position; } ));

        programData->blocks.push_back(block);

        return block;
    }

}

