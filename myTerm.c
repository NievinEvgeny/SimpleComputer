#include "myTerm.h"
#include <sys/ioctl.h> // для функции ioctl
#include <termios.h>   // для struct winsize
#include <unistd.h>    // для констант STDIN_FILENO, STDOUT_FILENO и STDERR_FILENO - это файловые дескрипторы

int mt_clrscr(void)
{
    printf("\E[2J\E[1;1H");
    return 0;
}

int mt_gotoXY(int X, int Y)
{
    int rows, cols;
    if (mt_getscreensize(&rows, &cols) == -1)
    {
        return -1;
    }
    if ((Y > cols) || (Y <= 0) || (X > rows) || (X <= 0))
    {
        return -1;
    }
    printf("\E[%d;%dH", Y, X);
    return 0;
}

int mt_getscreensize(int* rows, int* cols)
{
    struct winsize ws;
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws))
    {
        return -1;
    }
    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;
}

int mt_setfgcolor(enum colors color)
{
    if (color < COLOR_BLACK || color > COLOR_GREY)
    {
        return -1;
    }
    printf("\E[%dm", color + 30);
    return 0;
}

int mt_setbgcolor(enum colors color)
{
    if (color < COLOR_BLACK || color > COLOR_GREY)
    {
        return -1;
    }
    printf("\E[%dm", color + 40);
    return 0;
}