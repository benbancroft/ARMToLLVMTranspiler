#ifndef SINGLEDATATRANSFERINSTRUCTION_H
#define SINGLEDATATRANSFERINSTRUCTION_H

#include "arminstruction.h"

class SingleDataTransferInstruction : public ArmInstruction
{
private:
    bool immediateOffset;
    bool postPreIndexing;
    bool downOrUp;
    bool byteOrWord;
    bool doesWriteback;
    bool storeOrLoad;
    Register baseRegister;
    Register srcDestRegister;
    uint8_t offset;
public:
    SingleDataTransferInstruction(Condition condition, bool immediateOffset, bool postPreIndexing, bool downOrUp, bool byteOrWord, bool doesWriteback, bool storeOrLoad, Register baseRegister, Register srcDestRegister, uint8_t offset);

    const bool isImmediateOffset(){
        return immediateOffset;
    }
    const bool isPostOrPreIndexing(){
        return postPreIndexing;
    }
    const bool isStoreOrLoadTransfer(){
        return storeOrLoad;
    }
    const Register getBaseRegister(){
        return baseRegister;
    }
    const Register getSrcDestRegister(){
        return srcDestRegister;
    }
    const bool isDownUpOffset(){
        return downOrUp;
    }
    const bool isByteOrWord(){
        return byteOrWord;
    }
    const uint8_t getOffset(){
        return offset;
    }
};

#endif // SINGLEDATATRANSFERINSTRUCTION_H
