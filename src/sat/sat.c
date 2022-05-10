#include "sat.h"
#include <lib/SimpleComputer.h>
#include <stdio.h>
#include <string.h>

int arg2_assign(char* str, int* value)
{
    int pos = 0, plus = 1;
    int n;

    if (str[0] == '+')
    {
        plus = 0;
        pos = 1;
    }
    if (sscanf(str + pos, "%d", &n) != 1)
    {
        return -1;
    }
    if ((n > 0x3FFF) || (n < (int)(~0x3FFF)))
    {
        return -1;
    }
    *value = n | (plus << 14);
    return 0;
}

int arg2_command(char* str)
{
    if (strcmp(str, "READ") == 0)
        return 0x10;
    if (strcmp(str, "WRITE") == 0)
        return 0x11;
    if (strcmp(str, "LOAD") == 0)
        return 0x20;
    if (strcmp(str, "STORE") == 0)
        return 0x21;
    if (strcmp(str, "ADD") == 0)
        return 0x30;
    if (strcmp(str, "SUB") == 0)
        return 0x31;
    if (strcmp(str, "DIVIDE") == 0)
        return 0x32;
    if (strcmp(str, "MUL") == 0)
        return 0x33;
    if (strcmp(str, "JUMP") == 0)
        return 0x40;
    if (strcmp(str, "JNEG") == 0)
        return 0x41;
    if (strcmp(str, "JZ") == 0)
        return 0x42;
    if (strcmp(str, "HALT") == 0)
        return 0x43;
    if (strcmp(str, "RCR") == 0)
        return 0x63;
    return -1;
}

int pars_line(char* str, int* address, int* value)
{
    char* ptr;
    int operand, command;
    int assign = 0;

    ptr = strchr(str, ';');
    if (ptr != NULL)
    {
        *ptr = '\0';
    }
    ptr = strchr(str, '\n');
    if (ptr != NULL)
    {
        *ptr = '\0';
    }
    ptr = strtok(str, " \t");
    if (ptr == NULL)
    {
        return EMPTY_STR;
    }
    if (sscanf(ptr, "%d", address) != 1)
    {
        return ERR_ARG1;
    }
    if ((*address < 0) || (*address >= MEMORY_SIZE))
    {
        return ERR_ARG1;
    }
    ptr = strtok(NULL, " \t");
    if (ptr == NULL)
    {
        return ERR_FEW;
    }
    if (strcmp(ptr, "=") == 0)
    {
        assign = 1;
    }
    else
    {
        command = arg2_command(ptr);
        if (command == -1)
        {
            return ERR_ARG2;
        }
    }
    ptr = strtok(NULL, " \t");
    if (ptr == NULL)
    {
        return ERR_FEW;
    }
    if (!assign)
    {
        if (sscanf(ptr, "%d", &operand) != 1)
        {
            return ERR_ARG3;
        }
    }
    else
    {
        if (arg2_assign(ptr, value) == -1)
        {
            return ERR_ARG3;
        }
    }
    if ((operand < 0) || (operand >= MEMORY_SIZE))
    {
        return ERR_ARG3;
    }
    ptr = strtok(NULL, " \t");
    if (ptr != NULL)
    {
        return ERR_MANY;
    }
    if (!assign)
    {
        sc_commandEncode(command, operand, value);
    }
    return 0;
}

void print_error(char* line, int line_num, int err)
{
    switch (err)
    {
    case ERR_ARG1:
        printf("%d: Неверно задан адресс ячейки памяти\n", line_num);
        break;

    case ERR_ARG2:
        printf("%d: Неверно задана команда\n", line_num);
        break;

    case ERR_ARG3:
        printf("%d: Неверно задан операнд\n", line_num);
        break;

    case ERR_FEW:
        printf("%d: Недостаточное количество аргументов\n", line_num);
        break;

    case ERR_MANY:
        printf("%d: Избыточное количество аргументов\n", line_num);
        break;
    }
    printf("%s\n", line);
}

int check_argv(char* argv[])
{
    char *input, *output;

    input = strrchr(argv[1], '.');
    output = strrchr(argv[2], '.');
    if ((strcmp(input, ".sa") == 0) && (strcmp(output, ".o") == 0))
    {
        return 0;
    }
    return -1;
}

int main(int argc, char* argv[])
{
    char buf[256], line[256];
    FILE *input, *output;
    int value, address, line_num = 1;
    int err;

    if (argc != 3)
    {
        printf("Неправильные аргументы, пример: './sat sat.sa sat.o'\n");
        return -1;
    }
    if (check_argv(argv) != 0)
    {
        printf("Неправильные аргументы, пример: './sat sat.sa sat.o'\n");
        return -1;
    }
    if ((input = fopen(argv[1], "rb")) == NULL)
    {
        printf("ошибка открытия файла: %s\n", argv[1]);
        return -1;
    }
    if ((output = fopen(argv[2], "wb")) == NULL)
    {
        printf("ошибка открытия файла: %s\n", argv[2]);
        return -1;
    }

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        Memory[i] = 0;
    }

    while (fgets(line, 100, input))
    {
        strcpy(buf, line);
        err = pars_line(buf, &address, &value);
        if (err == 0)
        {
            if (Memory[address] == 0)
            {
                Memory[address] = value;
            }
            else
            {
                printf("%d: Команда с адресом %d уже существует\n%s", line_num, address, line);
            }
        }
        if (err < 0)
        {
            print_error(line, line_num, err);
        }
        line_num++;
    }
    if (err == 0)
    {
        fwrite(Memory, 1, MEMORY_SIZE * sizeof(int), output);
    }
    fclose(input);
    fclose(output);
    return 0;
}