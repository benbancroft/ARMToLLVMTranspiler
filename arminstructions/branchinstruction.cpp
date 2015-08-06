#include "branchinstruction.h"

BranchInstruction::BranchInstruction(Condition condition, bool linkedBranch, int32_t addressOffset) : ArmInstruction(condition, InstructionType::DataProcessing)
{
    this->linkedBranch = linkedBranch;
    this->addressOffset = addressOffset;
}
