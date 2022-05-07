#include "SimpleComputer.h"
#include "interface.h"
#include "units.h"
#include <signal.h>
#include <unistd.h>

void timer()
{
    draw_interface();
    CU();
    instructionCounter++;
    if (instructionCounter > 100)
    {
        instructionCounter = 0;
    }
    if (!CHECK_BIT(registr, T))
    {
        alarm(3);
    }
}

void usrsig()
{
    alarm(0);
    sc_memoryInit();
    sc_regInit();
    sc_regSet(T, 1);
    instructionCounter = 0;
    accumulator = 0;
}

void sig_Set()
{
    signal(SIGALRM, timer);
    signal(SIGUSR1, usrsig);
}