#pragma once

enum colors {
    COLOR_BLACK = 0,
    COLOR_RED = 1,
    COLOR_GREEN = 2,
    COLOR_YELLOW = 3,
    COLOR_BLUE = 4,
    COLOR_MAGENTA = 5,
    COLOR_CYAN = 6,
    COLOR_GREY = 7,
    COLOR_DEFAULT = 9
};

int mt_clrscr(void);
int mt_gotoXY(int X, int Y);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);