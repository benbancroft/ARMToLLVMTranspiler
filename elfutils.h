#ifndef ELFUTILS_H
#define ELFUTILS_H

#include <iostream>
#include <fstream>
#include <stdint.h>

#include "elfheader.h"

namespace Elf{

    uint16_t readInt16(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness);

    uint32_t readInt32(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness);

    uint64_t readInt64(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness);

    uint64_t readPointer(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness, BinaryClass binaryClass);

    uint64_t mapVirtualAddressToFile(uint64_t virtualAddress, ELFHeader* header);

}

#endif // ELFUTILS_H
