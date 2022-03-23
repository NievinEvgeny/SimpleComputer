#include "lib/SimpleComputer.h"
#include "lib/interface.h"
#include "lib/myBigChar.h"
#include "lib/myReadKey.h"
#include "lib/myTerm.h"
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