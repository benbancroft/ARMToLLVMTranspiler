#ifndef ELF_H
#define ELF_H

#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <byteswap.h>
#include <stdint.h>
#include <vector>

#include "utils.h"
#include "arminstructions/armutils.h"

//Might be an idea to move these out of here in future

#include "arminstructions/arminstruction.h"
#include "arminstructions/dataprocessinginstruction.h"
#include "arminstructions/singledatatransferinstruction.h"
#include "arminstructions/blockdatatransferinstruction.h"

enum OSABIType { System_V, HP_UX, NetBSD, Linux, Solaris, AIX, IRIX, FreeBSD, OpenBSD, OpenVMS };
enum BinaryType { Relocatable, Executable, Shared, Core };
enum Architecture { INVALID = 0x0, SPARC = 0x02, x86 = 0x03, MIPS = 0x08, PowerPC = 0x14, ARM = 0x28, SuperH = 0x2A, IA_64 = 0x32, x86_64 = 0x3E, AArch64 = 0xB7 };

struct ProgramSectionHeader
{
  uint32_t    type;                 /* Segment type */
  uint32_t    offset;               /* Segment file offset */
  uint32_t    virtualAddr;                /* Segment virtual address */
  uint32_t    physicalAddr;                /* Segment physical address */
  uint32_t    segmentFileSize;               /* Segment size in file */
  uint32_t    segmentMemSize;                /* Segment size in memory */
  uint32_t    segmentFlags;                /* Segment flags */
  uint32_t    SegmentAlignment;                /* Segment alignment */
};

struct ELFHeader{
    Utils::BinaryClass binaryClass;
    Utils::Endianness endianness;
    char identityVersion;
    OSABIType OSABI;
    BinaryType type;
    Architecture architecture;
    uint32_t version;
    uint64_t entryPoint;
    uint64_t programHeaderStart;
    uint64_t sectionHeaderStart;
    uint32_t flags;
    uint16_t elfHeaderSize;
    uint16_t programHeaderSize;
    uint16_t programHeaderEntries;
    uint16_t sectionHeaderSize;
    uint16_t sectionHeaderEntries;
    uint16_t sectionHeaderNamesIndex;
    std::vector<ProgramSectionHeader> programSectionHeaders;
    uint64_t binaryEntryPoint;

};

int readELF(std::string file);

#endif // ELF_H
