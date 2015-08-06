#ifndef SINGLEDATATRANSFERINSTRUCTION_H
#define SINGLEDATATRANSFERINSTRUCTION_H

#include "arminstruction.h"

class SingleDataTransferInstruction : public ArmInstruction
{
public:
    SingleDataTransferInstruction(Condition condition);
};

#endif // SINGLEDATATRANSFERINSTRUCTION_H
