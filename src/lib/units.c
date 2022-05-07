#include "SimpleComputer.h"
#include <stdio.h>

int ALU(int command, int operand)
{
    switch (command)
    {
    case 0x30: /* ADD */
        accumulator += Memory[operand];
        break;

    case 0x31: /* SUB */
        if (((Memory[operand] >> 14) & 1) == 1)
        {
            accumulator -= Memory[operand] | (~0x7FFF);
        }
        else
        {
            accumulator -= Memory[operand];
        }
        if ((accumulator > ((int)(~0x7FFF))) && (accumulator <= 0x7FFF))
        {
            accumulator &= 0x7FFF;
        }
        break;

    case 0x32: /* DIV */
        if (Memory[operand] != 0)
        {
            accumulator /= Memory[operand];
        }
        else
        {
            sc_regSet(O, 1);
            return -1;
        }
        break;

    case 0x33: /* MUL */
        accumulator *= Memory[operand];
        break;

    case 0x63: /* RCR */
        accumulator = (Memory[instructionCounter] >> 1) | ((Memory[instructionCounter] & 1) << 13);
        if ((accumulator > ((int)(~0x7FFF))) && (accumulator <= 0x7FFF))
        {
            accumulator &= 0x7FFF;
        }
        break;
    }

    return 0;
}

void CU()
{
    int command, operand, n;

    if (sc_commandDecode(Memory[instructionCounter], &command, &operand) != 0)
    {
        sc_regSet(T, 1);
        return;
    }
    if ((operand < 0) && (operand >= MEMORY_SIZE))
    {
        sc_regSet(M, 1);
        sc_regSet(T, 1);
        return;
    }
    if (((command >= 0x30) && (command <= 0x33)) || (command == 0x63))
    {
        if (ALU(command, operand) != 0)
        {
            sc_regSet(T, 1);
        }
    }
    else
    {
        switch (command)
        {
        case 0x10: /* READ */
            if (!scanf("%d", &n) || n > 0x3FFF || n < 0)
            {
                sc_regSet(P, 1);
                sc_regSet(T, 1);
            }
            else
            {
                Memory[operand] = n | 0x8000;
            }
            break;

        case 0x11: /* WRITE */
            printf("Ячейка №%d = %x", operand, Memory[instructionCounter] & 0x7FFF);
            break;

        case 0x20: /* LOAD */
            accumulator = Memory[operand];
            break;

        case 0x21: /* STORE */
            Memory[operand] = accumulator;
            break;

        case 0x40: /* JUMP */
            instructionCounter = operand - 1;
            break;

        case 0x41: /* JNEG */
            if (((accumulator >> 14) & 1) == 1)
            {
                instructionCounter = operand - 1;
            }
            break;

        case 0x42: /* JZ */
            if (accumulator == 0)
            {
                instructionCounter = operand - 1;
            }
            break;

        case 0x43: /* HALT */
            sc_regSet(T, 1);
            break;
        }
    }
}