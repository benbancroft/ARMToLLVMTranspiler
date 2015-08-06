#ifndef DATAPROCESSINGINSTRUCTION_H
#define DATAPROCESSINGINSTRUCTION_H

#include "arminstruction.h"

enum DataProcessingInstructionTypes { AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, TEQ, CMP, CMN, ORR, MOV, BIC, MVN };

class DataProcessingInstruction : public ArmInstruction
{
private:
    bool immediateForm;
    DataProcessingInstructionTypes mnemonic;
public:
    DataProcessingInstruction(Condition condition, bool immediateForm, DataProcessingInstructionTypes mnemonic);
};

#endif // DATAPROCESSINGINSTRUCTION_H
