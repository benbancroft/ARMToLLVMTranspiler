#ifndef ARMUTILS_H
#define ARMUTILS_H

#include "elf.h"

class ArmInstruction;
struct ELFHeader;

namespace Arm{

    ArmInstruction* ReadInstruction(std::ifstream* file, Utils::Endianness endianness, ELFHeader* header);

}

#endif // ARMUTILS_H
