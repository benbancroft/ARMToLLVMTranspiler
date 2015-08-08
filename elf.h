#ifndef ELF_H
#define ELF_H

#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <byteswap.h>
#include <stdint.h>
#include <vector>
#include <algorithm>

#include "elfutils.h"
#include "arminstructions/armutils.h"
#include "basicblock.h"

#include "elfheader.h"

//Might be an idea to move these out of here in future

#include "arminstructions/arminstruction.h"
#include "arminstructions/dataprocessinginstruction.h"
#include "arminstructions/singledatatransferinstruction.h"
#include "arminstructions/blockdatatransferinstruction.h"
#include "arminstructions/branchinstruction.h"

namespace Elf{

    int readELF(std::string file);

}

#endif // ELF_H
