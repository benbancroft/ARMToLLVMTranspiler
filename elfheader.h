#ifndef ELFHEADER_H
#define ELFHEADER_H

#include <vector>

namespace Elf{

    enum OSABIType { System_V, HP_UX, NetBSD, Linux, Solaris, AIX, IRIX, FreeBSD, OpenBSD, OpenVMS };
    enum BinaryType { Relocatable, Executable, Shared, Core };
    enum Architecture { INVALID = 0x0, SPARC = 0x02, x86 = 0x03, MIPS = 0x08, PowerPC = 0x14, ARM = 0x28, SuperH = 0x2A, IA_64 = 0x32, x86_64 = 0x3E, AArch64 = 0xB7 };

    enum Endianness { Little = 1, Big = 2 };
    enum BinaryClass { b32 = 1, b64 = 2 };

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
        BinaryClass binaryClass;
        Endianness endianness;
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

}

#endif // ELFHEADER_H
