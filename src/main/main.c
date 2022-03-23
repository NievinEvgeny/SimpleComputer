#include "lib/SimpleComputer.h"
#include "lib/interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

int main()
{
    sc_memoryInit();
    sc_regInit();
    accumulator = 0;
    instructionCounter = 0;
    run_interface();
    return 0;
}