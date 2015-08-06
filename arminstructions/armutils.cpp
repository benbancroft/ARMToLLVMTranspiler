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
                //return new BranchInstruction(condition);
            }
        }break;
        }


        return NULL;
    }

}

