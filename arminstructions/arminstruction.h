#ifndef ARMINSTRUCTION_H
#define ARMINSTRUCTION_H

#include <iostream>
#include <fstream>
#include <stdint.h>

#include "utils.h"

struct ELFHeader;

enum Condition { EQ, NE, CS, CC, MI, PL, VS, HI, LS, GE, LT, GT, LE, AL };

enum InstructionType { Invalid, DataProcessing, Multiply, SoftwareInterrupt, SingleDataTransfer, Undefined, BlockDataTransfer, Branch };

class ArmInstruction
{
private:
    Condition condition;
    InstructionType type;
public:
    ArmInstruction(Condition condition, InstructionType type);
};

#endif // ARMINSTRUCTION_H
