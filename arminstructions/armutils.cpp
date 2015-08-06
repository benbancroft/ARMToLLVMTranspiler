#include "armutils.h"

namespace Arm{

    ArmInstruction* ReadInstruction(std::ifstream* file, Utils::Endianness endianness, ELFHeader* header){
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
                return new SingleDataTransferInstruction(condition);
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

}

