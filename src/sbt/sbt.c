#include "sbt.h"
#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 256

int check_argv(char* argv[])
{
    char *input, *output;

    input = strrchr(argv[1], '.');
    output = strrchr(argv[2], '.');
    if ((strcmp(input, ".sb") == 0) && (strcmp(output, ".sa") == 0))
    {
        return 0;
    }
    return -1;
}

int get_tokens(char* line, int* line_index, char* keyword)
{
    char* ptr = strtok(line, " \t\n");

    if (ptr == NULL)
    {
        return 1;
    }
    if (sscanf(ptr, "%d", line_index) != 1)
    {
        return -1;
    }
    ptr = strtok(NULL, " \t\n");
    if (ptr == NULL)
    {
        return -1;
    }
    if (sscanf(ptr, "%s", keyword) != 1)
    {
        return -1;
    }
    ptr = strtok(NULL, "\0\n");
    if (ptr == NULL)
    {
        return 0;
    }
    strcpy(line, ptr);
}

int main(int argc, char* argv[])
{
    char keyw_str[256], line[256];
    FILE *input, *output;
    int keyw; //Команда (второй аргумент sb)
    int line_index; //Индекс строки (первый аргумент sb)

    if (argc != 3)
    {
        printf("Неправильные аргументы, пример: './sbt sbt.sb s.sa'\n");
        return -1;
    }
    if (check_argv(argv) != 0)
    {
        printf("Неправильные аргументы, пример: './sbt sbt.sb s.sa'\n");
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

    while (fgets(line, MAXLINES, input))
    {
        int check_tokens = get_tokens(line, &line_index, keyw_str);

        if (check_tokens == -1)
        {
            fprintf(output, "Ошибка программы\n");
            return -1;
        }
        if (check_tokens == 1)
        {
            continue;
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}