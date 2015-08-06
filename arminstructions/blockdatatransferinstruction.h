#ifndef BLOCKDATATRANSFERINSTRUCTION_H
#define BLOCKDATATRANSFERINSTRUCTION_H

#include "arminstruction.h"

class BlockDataTransferInstruction : public ArmInstruction
{
public:
    BlockDataTransferInstruction(Condition condition);
};

#endif // BLOCKDATATRANSFERINSTRUCTION_H
