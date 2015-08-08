#ifndef ARMUTILS_H
#define ARMUTILS_H

#include <vector>
#include <set>

#include "utils.h"

#include "elf.h"
#include "basicblock.h"

class ArmInstruction;
struct ELFHeader;

namespace Arm{

    struct ProgramData{
        std::vector<BasicBlock*> blocks;
        std::set<int> dataAddresses;
        int position = 0;
    };

    ArmInstruction* ReadInstruction(std::ifstream* file, Elf::Endianness endianness, Elf::ELFHeader* header);
    BasicBlock* HandleInstruction(ProgramData* programData, Elf::Endianness systemEndianness, std::ifstream* binary, Elf::ELFHeader* header);

}

#endif // ARMUTILS_H
