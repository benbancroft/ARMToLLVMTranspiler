#include "elf.h"
using namespace std;

int readELF(std::string file)
{
    streampos begin,end;
    ifstream binary(file.c_str(), ios::binary);

    //read magic bytes
    string magic(4 , ' ');
    binary.read(&magic[0], 4);

    if (!magic.compare("\x7FELF")){
        cout << magic << endl;
        cerr << "Invalid elf file - magic bytes are wrong" << endl;
        return 1;
    }

    ELFHeader header;
    Utils::Endianness systemEndianness = htonl(47) == 47 ? Utils::Endianness::Big : Utils::Endianness::Little;

    char binaryClass;
    binary.read(&binaryClass, 1);
    header.binaryClass = static_cast<Utils::BinaryClass>(binaryClass);

    //used from 0x10 onwards.
    char endianness;
    binary.read(&endianness, 1);
    header.endianness = static_cast<Utils::Endianness>(endianness);

    binary.read(&header.identityVersion, 1);

    char OSABI;
    binary.read(&OSABI, 1);
    header.OSABI = static_cast<OSABIType>(OSABI);

    //unused as per specification
    binary.ignore(8);

    //We now need to take into account endianness :(

    header.type = static_cast<BinaryType>(readInt16(&binary, systemEndianness, header.endianness));
    header.architecture = static_cast<Architecture>(readInt16(&binary, systemEndianness, header.endianness));
    header.version = readInt32(&binary, systemEndianness, header.endianness);

    //The following are 64bit on 64bit architecures. Store in unint64_t to prevent overflow occuring.

    header.entryPoint = readPointer(&binary, systemEndianness, header.endianness, header.binaryClass);
    header.programHeaderStart = readPointer(&binary, systemEndianness, header.endianness, header.binaryClass);
    header.sectionHeaderStart = readPointer(&binary, systemEndianness, header.endianness, header.binaryClass);

    header.flags = readInt32(&binary, systemEndianness, header.endianness);
    header.elfHeaderSize = readInt16(&binary, systemEndianness, header.endianness);
    header.programHeaderSize = readInt16(&binary, systemEndianness, header.endianness);
    header.programHeaderEntries = readInt16(&binary, systemEndianness, header.endianness);
    header.sectionHeaderSize = readInt16(&binary, systemEndianness, header.endianness);
    header.sectionHeaderEntries = readInt16(&binary, systemEndianness, header.endianness);
    header.sectionHeaderNamesIndex = readInt16(&binary, systemEndianness, header.endianness);

    //now we jump to the program headers

    binary.seekg(header.programHeaderStart);

    //header.programSectionHeaders

    for (int i = 0; i < header.programHeaderEntries; i++){
        ProgramSectionHeader section;

        section.type = readInt32(&binary, systemEndianness, header.endianness);
        section.offset = readInt32(&binary, systemEndianness, header.endianness);
        section.virtualAddr = readInt32(&binary, systemEndianness, header.endianness);
        section.physicalAddr = readInt32(&binary, systemEndianness, header.endianness);
        section.segmentFileSize = readInt32(&binary, systemEndianness, header.endianness);
        section.segmentMemSize = readInt32(&binary, systemEndianness, header.endianness);
        section.segmentFlags = readInt32(&binary, systemEndianness, header.endianness);
        section.SegmentAlignment = readInt32(&binary, systemEndianness, header.endianness);

        header.programSectionHeaders.push_back(section);
    }

    //now we need to map the virtual entry point against the binary.
    header.binaryEntryPoint = 0;
    for (ProgramSectionHeader &section : header.programSectionHeaders){
        if (header.entryPoint >= section.virtualAddr && section.virtualAddr + section.segmentMemSize >= header.entryPoint){
            header.binaryEntryPoint = header.entryPoint - section.virtualAddr + section.offset;
        }
    }

    if (header.binaryEntryPoint <= header.elfHeaderSize){
        cout << magic << endl;
        cerr << "Invalid entry point - cannot be inside elf header" << endl;
        return 1;
    }

    cout << "Entry Point - Virtual address: " << hex << header.entryPoint << ", file offset: " << header.binaryEntryPoint << endl;

    //now we seek to start address

    binary.seekg(header.binaryEntryPoint);

    while (true){
        ArmInstruction* inst = static_cast<DataProcessingInstruction*>(Arm::ReadInstruction(&binary, systemEndianness, &header));
    }

    /*begin = binary.tellg();
    binary.seekg (0, ios::end);
    end = binary.tellg();
    binary.close();
    cout << "size is: " << (end-begin) << " bytes." << endl;*/

    return 0;
}
