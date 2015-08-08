#include "singledatatransferinstruction.h"

SingleDataTransferInstruction::SingleDataTransferInstruction(Condition condition, bool immediateOffset, bool postPreIndexing, bool downOrUp, bool byteOrWord, bool doesWriteback, bool storeOrLoad, Register baseRegister, Register srcDestRegister, uint8_t offset) : ArmInstruction(condition, InstructionType::SingleDataTransfer)
{
    this->immediateOffset = immediateOffset;
    this->postPreIndexing = postPreIndexing;
    this->downOrUp = downOrUp;
    this->byteOrWord = byteOrWord;
    this->doesWriteback = doesWriteback;
    this->storeOrLoad = storeOrLoad;
    this->baseRegister = baseRegister;
    this->srcDestRegister = srcDestRegister;
    this->offset = offset;
}
