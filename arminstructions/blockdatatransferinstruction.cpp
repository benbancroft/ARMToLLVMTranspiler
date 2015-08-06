#include "blockdatatransferinstruction.h"

BlockDataTransferInstruction::BlockDataTransferInstruction(Condition condition) : ArmInstruction(condition, InstructionType::SingleDataTransfer)
{
}
