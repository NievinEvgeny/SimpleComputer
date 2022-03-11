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
    int value2;
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        sc_commandEncode(42, rand() % 126, &value2);
        sc_memorySet(i, value2);
    }
    accumulator = 0;
    instructionCounter = 0;
    run_interface();

    /*
    struct termios options;
    enum keys pressed_key;
    while (pressed_key != KEY_q)
    {
        rk_readkey(&pressed_key);
        printf(" key = %d\n", pressed_key);
    }
    rk_mytermregime(0, 1, 0, 0, 1);

    rk_mytermsave();
    tcgetattr(TCSANOW, &options);
    printf("lflag = %d\n", options.c_lflag);
    printf("vtime = %d\n", options.c_cc[VTIME]);
    printf("vmin = %d\n", options.c_cc[VMIN]);
    printf("\n");

    rk_mytermregime(0, 0, 1, 1, 0);
    tcgetattr(TCSANOW, &options);
    printf("lflag = %d\n", options.c_lflag);
    printf("vtime = %d\n", options.c_cc[VTIME]);
    printf("vmin = %d\n", options.c_cc[VMIN]);
    printf("\n");

    rk_mytermrestore();
    tcgetattr(TCSANOW, &options);
    printf("lflag = %d\n", options.c_lflag);
    printf("vtime = %d\n", options.c_cc[VTIME]);
    printf("vmin = %d\n", options.c_cc[VMIN]);
    printf("\n");
    rk_mytermregime(0, 0, 0, 1, 0);
    rk_mytermregime(1, 0, 0, 0, 0);
    */
    return 0;
}