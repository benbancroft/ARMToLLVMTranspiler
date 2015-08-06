#ifndef BRANCHINSTRUCTION_H
#define BRANCHINSTRUCTION_H

#include "arminstruction.h"

class BranchInstruction : public ArmInstruction
{
private:
    bool linkedBranch;
    int32_t addressOffset;
public:
    BranchInstruction(Condition condition, bool linkedBranch, int32_t addressOffset);
};

#endif // BRANCHINSTRUCTION_H
