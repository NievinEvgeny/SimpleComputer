#include "interface.h"
#include "SimpleComputer.h"
#include "myBigChar.h"
#include "myTerm.h"
#include <stdio.h>

void show_interface()
{
    print_memory();
    print_cell();
    print_keys();
    print_accum();
    print_instrcntr();
    print_operation();
    print_flags();
    mt_gotoXY(1, 25);
}

void print_memory()
{
    bc_box(1, 1, 63, 13);
    mt_gotoXY(28, 1);
    printf(" Memory ");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            mt_gotoXY(2 + j * 6, i + 2);
            printf("+%x ", Memory[i * 10 + j]);
        }
    }
}

void print_cell()
{
    int memvalue = Memory[instructionCounter];
    bc_box(1, 13, 51, 23);
    for (int i = 4; i > 0; i--)
    {
        bc_printbigchar(bcAll[memvalue % 16], 2 + 10 * i, 14, COLOR_GREY, COLOR_BLACK);
        memvalue /= 16;
    }
    bc_printbigchar(bcp, 2, 14, COLOR_GREY, COLOR_BLACK);
}

void print_keys()
{
    bc_box(52, 13, 88, 23);
    mt_gotoXY(55, 13);
    printf(" Keys: ");
    mt_gotoXY(53, 14);
    printf("l   - load");
    mt_gotoXY(53, 15);
    printf("s   - save");
    mt_gotoXY(53, 16);
    printf("r   - run");
    mt_gotoXY(53, 17);
    printf("t   - step");
    mt_gotoXY(53, 18);
    printf("i   - reset");
    mt_gotoXY(53, 19);
    printf("F5  - accumulator");
    mt_gotoXY(53, 20);
    printf("F6  - instructionCounter");
}

void print_accum()
{
    bc_box(64, 1, 88, 4);
    mt_gotoXY(70, 1);
    printf("accumulator");
    mt_gotoXY(74, 2);
    printf("+%x", accumulator);
}

void print_instrcntr()
{
    bc_box(64, 4, 88, 7);
    mt_gotoXY(67, 4);
    printf("instructionCounter");
    mt_gotoXY(76, 5);
    printf("%d", instructionCounter);
}

void print_operation()
{
    bc_box(64, 7, 88, 10);
    mt_gotoXY(72, 7);
    printf("operation");
    mt_gotoXY(75, 8);
    printf("???");
}

void print_flags()
{
    bc_box(64, 10, 88, 13);
    mt_gotoXY(74, 10);
    printf("flags");
    mt_gotoXY(71, 11);
    printf("P O M E T");
}