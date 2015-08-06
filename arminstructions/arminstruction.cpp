#include "arminstruction.h"

ArmInstruction::ArmInstruction(Condition condition, InstructionType type)
{
    this->condition = condition;
    this->type = type;
}
