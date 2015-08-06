#include "elf.h"
using namespace std;

const string file = "example-arm";

int main()
{
    //add some checks in here, maybe even move magic check incase more binary formats are added (PE?)

    return readELF(file);
}

