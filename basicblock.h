#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include <stdint.h>
#include <vector>

#include "arminstructions/arminstruction.h"

class BasicBlock
{
private:
    uint32_t startAddress;
public:
    BasicBlock(uint32_t startAddress);
    std::vector<ArmInstruction*> blocks;
    const int32_t GetStartAddress(){
        return startAddress;
    }
};

#endif // BASICBLOCK_H
