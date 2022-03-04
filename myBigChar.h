#pragma once

#include "myTerm.h"

#define bc_cornerUpLeft "l"
#define bc_cornerDownLeft "m"
#define bc_cornerUpRight "k"
#define bc_cornerDownRight "j"
#define bc_horizontaleLine "q"
#define bc_verticalLine "x"

static int bc0[2] = {3284402175, 4294951875};
static int bc1[2] = {421207580, 4279769112};
static int bc2[2] = {3233857791, 4278387711};
static int bc3[2] = {4290822399, 4290822336};
static int bc4[2] = {859192376, 808517425};
static int bc5[2] = {2130904063, 2143338688};
static int bc6[2] = {1023525758, 2126741955};
static int bc7[2] = {811647231, 50727960};
static int bc8[2] = {2126758782, 2126758851};
static int bc9[2] = {3284386686, 2126758142};
static int bcA[2] = {606345240, 2172747330};
static int bcB[2] = {1063502719, 2143535971};
static int bcC[2] = {63137340, 1013367555};
static int bcD[2] = {3284362047, 1063502787};
static int bcE[2] = {4278387711, 4278387459};
static int bcF[2] = {50529279, 50529151};
static int bcp[2] = {4279769112, 404232447}; // +
static int bcm[2] = {4278190080, 255};       // -
static int* bcAll[16] = {bc0, bc1, bc2, bc3, bc4, bc5, bc6, bc7, bc8, bc9, bcA, bcB, bcC, bcD, bcE, bcF};

int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int a[2], int x, int y, enum colors f_color, enum colors b_color);
int bc_setbigcharpos(int* big, int x, int y, int value);
int bc_getbigcharpos(int* big, int x, int y, int* value);
int bc_bigcharwrite(int fd, int* big, int count);
int bc_bigcharread(int fd, int* big, int need_count, int* count);