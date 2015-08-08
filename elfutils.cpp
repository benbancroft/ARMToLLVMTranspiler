#include "elfutils.h"

namespace Elf{

    uint16_t readInt16(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness){

        uint16_t value;
        //read as big on little
        file->read((char*)&value, 2);

        if (systemEndianness != Endianness::Big && binaryEndianness == Endianness::Big){
            value = be16toh(value);
        }else if (systemEndianness != Endianness::Little && binaryEndianness == Endianness::Little){
            value = le16toh(value);
        }

        return value;
    }

    uint32_t readInt32(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness){

        uint32_t value;
        file->read((char*)&value, 4);

        if (systemEndianness != Endianness::Big && binaryEndianness == Endianness::Big){
            value = be32toh(value);
        }else if (systemEndianness != Endianness::Little && binaryEndianness == Endianness::Little){
            value = le32toh(value);
        }

        return value;
    }

    uint64_t readInt64(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness){

        uint64_t value;
        file->read((char*)&value, 8);

        if (systemEndianness != Endianness::Big && binaryEndianness == Endianness::Big){
            value = be64toh(value);
        }else if (systemEndianness != Endianness::Little && binaryEndianness == Endianness::Little){
            value = le64toh(value);
        }

        return value;
    }

    uint64_t readPointer(std::ifstream* file, Endianness systemEndianness, Endianness binaryEndianness, BinaryClass binaryClass){
        if (binaryClass == BinaryClass::b64){
            return readInt64(file, systemEndianness, binaryEndianness);
        }else{
            return readInt32(file, systemEndianness, binaryEndianness);
        }
    }

    uint64_t mapVirtualAddressToFile(uint64_t virtualAddress, ELFHeader* header){
        //now we need to map the virtual entry point against the binary.
        for (ProgramSectionHeader &section : header->programSectionHeaders){
            if (virtualAddress >= section.virtualAddr && section.virtualAddr + section.segmentMemSize >= virtualAddress){
                return virtualAddress - section.virtualAddr + section.offset;
            }
        }
    }

}
