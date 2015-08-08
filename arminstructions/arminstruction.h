#ifndef ARMINSTRUCTION_H
#define ARMINSTRUCTION_H

#include <iostream>
#include <fstream>
#include <stdint.h>

#include "elfutils.h"

struct ELFHeader;

enum Condition { EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL, NV };

enum Register { R0, R1, R2, R3, R4, R5, R6, R7, R8, SB, R10, R11, IP, SP, LR, PC };

enum InstructionType { Invalid, DataProcessing, Multiply, SoftwareInterrupt, SingleDataTransfer, Undefined, BlockDataTransfer, Branch };

class ArmInstruction
{
private:
    Condition condition;
    InstructionType type;
public:
    ArmInstruction(Condition condition, InstructionType type);
    const InstructionType GetType(){
        return type;
    }
    const Condition GetCondition(){
        return condition;
    }
};

#endif // ARMINSTRUCTION_H
