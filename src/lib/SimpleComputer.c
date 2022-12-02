#include "SimpleComputer.h"
#include <stdio.h>

int registr;
int Memory[MEMORY_SIZE];
int accumulator;
int instructionCounter;

void sc_memoryInit()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        sc_memorySet(i, 0x0);
    }
}

int sc_memorySet(int address, int value)
{
    if ((address > MEMORY_SIZE) || (address < 0))
    {
        printf("Выход за границы памяти");
        sc_regSet(M, 1);
        return -1;
    }
    Memory[address] = value;
    return 0;
}

int sc_memoryGet(int address, int* value)
{
    if ((address > MEMORY_SIZE) || (address < 0))
    {
        printf("Выход за границы памяти");
        sc_regSet(M, 1);
        return -1;
    }
    *value = Memory[address];
    return *value;
}

int sc_memorySave(char* filename)
{
    FILE* out = fopen(filename, "wb");
    if (out == NULL)
    {
        printf("Невозможно открыть файл");
        return -1;
    }
    fwrite(Memory, sizeof(int), 100, out);
    fclose(out);
    return 0;
}

int sc_memoryLoad(char* filename)
{
    FILE* in = fopen(filename, "rb");
    if (in == NULL)
    {
        printf("Невозможно открыть файл");
        return -1;
    }
    fread(Memory, sizeof(int), 100, in);
    fclose(in);
    return 0;
}

void sc_regInit()
{
    for (int i = 1; i <= 5; i++)
    {
        sc_regSet(i, 0);
    }
}

int sc_regSet(int flag, int value)
{
    if ((flag < 1) || (flag > 6))
    {
        return -1;
    }
    else
    {
        if (value == 1)
        {
            registr = registr | (1 << flag);
            return 0;
        }
        if (value == 0)
        {
            registr = registr & (~(1 << flag));
            return 0;
        }
    }
}

int sc_regGet(int flag, int* value)
{
    if ((flag < 1) || (flag > 6))
    {
        return -1;
    }
    else
    {
        *value = (registr >> (flag - 1)) & 0x1;
        return *value;
    }
}

int sc_commandEncode(int command, int operand, int* value)
{
    if (operand > 100 || operand < 0)
    {
        printf("Неправильный операнд");
        return -1;
    }
    if ((command >= 0x51 && command <= 0x76) || (command >= 0x40 && command <= 0x43) || (command >= 0x30 && command <= 0x33)
        || (command >= 0x20 && command <= 0x21) || (command >= 0x10 && command <= 0x11))
    {
        *value = ((command << 7) | operand) & (~(1 << 15));
        return *value;
    }
    printf("Неправильная команда");
    return -1;
}

int sc_commandDecode(int value, int* command, int* operand)
{
    if (((value >> 15) & 0x1) != 0)
    {
        sc_regSet(E, 1);
        return -1;
    }
    *command = value & 0x3F80;
    *command = *command >> 7;
    *operand = value & 0x7F;
    sc_regSet(E, 0);
    return 0;
}