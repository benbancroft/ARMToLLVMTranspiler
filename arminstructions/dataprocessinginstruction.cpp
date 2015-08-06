#include "dataprocessinginstruction.h"

DataProcessingInstruction::DataProcessingInstruction(Condition condition, bool immediateForm, DataProcessingInstructionTypes mnemonic) : ArmInstruction(condition, InstructionType::DataProcessing)
{
    this->immediateForm = immediateForm;
    this->mnemonic = mnemonic;
}
