#include "SimpleComputer.h"
#include "interface.h"
#include <signal.h>
#include <unistd.h>

void timer(int sig)
{
    draw_interface();
    instructionCounter++;
    if (!CHECK_BIT(registr, I))
    {
        alarm(1);
    }
}

void usrsig(int sig)
{
    alarm(0);
    sc_memoryInit();
    sc_regInit();
    sc_regSet(I, 1);
    instructionCounter = 0;
    accumulator = 0;
}

void sig_Set()
{
    signal(SIGALRM, timer);
    signal(SIGUSR1, usrsig);
}