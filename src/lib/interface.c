#include "interface.h"
#include "SimpleComputer.h"
#include "myBigChar.h"
#include "myReadKey.h"
#include "myTerm.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cursorX = 0, cursorY = 0;

void run_interface()
{
    enum keys pressedKey;
    rk_mytermregime(0, 1, 0, 1, 1);
    while (pressedKey != KEY_q)
    {
        draw_interface();
        rk_readkey(&pressedKey);
        do_pressedKey(pressedKey);
    }
}

int do_pressedKey(enum keys pressedKey)
{
    if (CHECK_BIT(registr, T))
    {
        if (pressedKey == KEY_other)
        {
            return 0;
        }
        if (pressedKey == KEY_s)
        {
            printf("\nВведите имя файла: ");
            rk_mytermregime(1, 0, 0, 0, 0);
            char filename[100];
            fgets(filename, 100, stdin);
            filename[strlen(filename) - 1] = '\0';
            rk_mytermregime(0, 1, 0, 1, 1);
            if (sc_memorySave(filename) == 0)
            {
                return 0;
            }
            return -1;
        }
        if (pressedKey == KEY_l)
        {
            printf("\nВведите имя файла: ");
            rk_mytermregime(1, 0, 0, 0, 0);
            char filename[100];
            fgets(filename, 100, stdin);
            filename[strlen(filename) - 1] = '\0';
            rk_mytermregime(0, 1, 0, 1, 1);
            if (sc_memoryLoad(filename) == 0)
            {
                return 0;
            }
            return -1;
        }
        if (pressedKey == KEY_f5)
        {
            rk_mytermregime(1, 0, 0, 0, 0);
            char buffer[5];
            if (read(0, &buffer, 4) == 4)
            {
                while (getchar() != '\n')
                {
                }
            }
            int value = atoi(buffer);
            if (value > 9999)
            {
                return -1;
            }
            accumulator = value;
            rk_mytermregime(0, 1, 0, 1, 1);
            return 0;
        }
        if (pressedKey == KEY_f6)
        {
            rk_mytermregime(1, 0, 0, 0, 0);
            char buffer[3];
            if (read(0, &buffer, 2) == 2)
            {
                while (getchar() != '\n')
                {
                }
            }
            int value = atoi(buffer);
            if (value > 99)
            {
                return -1;
            }
            instructionCounter = value;
            rk_mytermregime(0, 1, 0, 1, 1);
            return 0;
        }
        if (pressedKey == KEY_left)
        {
            if (cursorX > 0)
            {
                cursorX -= 1;
                mt_gotoXY(cursorX, cursorY);
            }
            return 0;
        }
        if (pressedKey == KEY_right)
        {
            if (cursorX < 9)
            {
                cursorX += 1;
                mt_gotoXY(cursorX, cursorY);
            }
            return 0;
        }
        if (pressedKey == KEY_up)
        {
            if (cursorY > 0)
            {
                cursorY -= 1;
                mt_gotoXY(cursorX, cursorY);
            }
            return 0;
        }
        if (pressedKey == KEY_down)
        {
            if (cursorY < 9)
            {
                cursorY += 1;
                mt_gotoXY(cursorX, cursorY);
            }
            return 0;
        }
        if (pressedKey == KEY_enter)
        {
            rk_mytermregime(1, 0, 0, 0, 0);
            char buffer[5];
            if (read(0, &buffer, 4) == 4)
            {
                while (getchar() != '\n')
                {
                }
            }
            int value = atoi(buffer);
            if (value > 9999)
            {
                return -1;
            }
            Memory[cursorY * 10 + cursorX] = value;
            rk_mytermregime(0, 1, 0, 1, 1);
            return 0;
        }
        if (pressedKey == KEY_t)
        {
            raise(SIGALRM);
        }
    }
    if (pressedKey == KEY_i)
    {
        raise(SIGUSR1);
    }
    if (pressedKey == KEY_r)
    {
        if (CHECK_BIT(registr, T))
        {
            sc_regSet(T, 0);
            raise(SIGALRM);
        }
        else
        {
            alarm(0);
            sc_regSet(T, 1);
        }
    }
}

void draw_interface()
{
    mt_clrscr();
    print_memory();
    print_cell();
    print_keys();
    print_accum();
    print_instrcntr();
    print_operation();
    print_flags();
    print_IO();
}

void print_IO()
{
    mt_gotoXY(1, 23);
    printf("Input/Output:\n");
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
            if ((i * 10 + j) == (cursorY * 10 + cursorX))
            {
                mt_setfgcolor(COLOR_BLACK);
                mt_setbgcolor(COLOR_RED);
            }
            mt_gotoXY(2 + j * 6, i + 2);
            printf("+%0*x ", 4, Memory[i * 10 + j]);
            if ((i * 10 + j) == (cursorY * 10 + cursorX))
            {
                mt_setfgcolor(COLOR_DEFAULT);
                mt_setbgcolor(COLOR_DEFAULT);
            }
        }
    }
}

void print_cell()
{
    int memvalue = Memory[cursorY * 10 + cursorX];
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
    printf(" accumulator ");
    mt_gotoXY(75, 2);
    printf("+%x", accumulator);
}

void print_instrcntr()
{
    bc_box(64, 4, 88, 7);
    mt_gotoXY(66, 4);
    printf(" instructionCounter ");
    mt_gotoXY(76, 5);
    printf("%d", instructionCounter);
}

void print_operation()
{
    bc_box(64, 7, 88, 10);
    mt_gotoXY(71, 7);
    printf(" operation ");
    mt_gotoXY(72, 8);
    int command, operand, isCommand;
    isCommand = (Memory[cursorY * 10 + cursorX] >> 15) & 1;
    sc_commandDecode(Memory[cursorY * 10 + cursorX], &command, &operand);
    if (isCommand == 0)
        printf("+");
    else
        printf(" ");
    printf("%02x : %02x", command >> 7, operand);
}

void print_flags()
{
    bc_box(64, 10, 88, 13);
    mt_gotoXY(73, 10);
    printf(" flags ");
    mt_gotoXY(73, 11);
    if (CHECK_BIT(registr, P))
        printf("P");
    else
        printf(" ");
    if (CHECK_BIT(registr, O))
        printf("O");
    else
        printf(" ");
    if (CHECK_BIT(registr, M))
        printf("M");
    else
        printf(" ");
    if (CHECK_BIT(registr, T))
        printf("T");
    else
        printf(" ");
    if (CHECK_BIT(registr, E))
        printf("E");
    else
        printf(" ");
}