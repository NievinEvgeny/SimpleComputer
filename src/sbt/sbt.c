#include "sbt.h"
#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int check_line_indexes(int line_num, int lines[MAXLINES])
{
    if (line_num > 0)
    {
        if (lines[line_num - 1] >= lines[line_num])
        {
            return -1;
        }
    }
    return 0;
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
    return 0;
}

int get_keyword_code(char* str)
{
    if (strcmp(str, "REM") == 0)
        return KEYW_REM;
    if (strcmp(str, "INPUT") == 0)
        return KEYW_INPUT;
    if (strcmp(str, "OUTPUT") == 0)
        return KEYW_OUTPUT;
    if (strcmp(str, "GOTO") == 0)
        return KEYW_GOTO;
    if (strcmp(str, "IF") == 0)
        return KEYW_IF;
    if (strcmp(str, "LET") == 0)
        return KEYW_LET;
    if ((strcmp(str, "END") == 0) || (strcmp(str, "END\n") == 0))
        return KEYW_END;

    return -1;
}

int check_in_out(char* str)
{
    int flag = 0;
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        if (!(str[i] >= 'A' && str[i] <= 'Z'))
        {
            return -1;
        }
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            flag++;
        }
        else
        {
            flag = 0;
        }
        if (flag > 1)
        {
            return -1;
        }
    }
    return 0;
}

int check_goto(char* str, int lines[2][MAXLINES])
{
    char* ptr;
    int index = strtol(str, &ptr, 10);
    if (*ptr != '\n' && *ptr != '\0')
    {
        return -1;
    }
    for (int i = 0; i < MAXLINES; i++)
    {
        if (index == lines[0][i])
        {
            return lines[1][i - 1] + 1;
        }
    }
    return -1;
}

int sa_start_line(int lines[2][MAXLINES], int sb_line)
{
    if (sb_line == 0)
    {
        return 0;
    }
    return lines[1][sb_line - 1] + 1;
}

int check_letter_cell(char cell, int* letters)
{
    for (int i = 0; i < ALPHABET; i++)
    {
        if (letters[cell - 'A'] != -1)
        {
            return 0;
        }
    }
    return -1;
}

int parsing(int lines[2][MAXLINES], int sb_line, int* var_num, int key, char* str, int* letters, FILE* output)
{
    int sa_line = sa_start_line(lines, sb_line);

    switch (key)
    {
    case KEYW_INPUT:
        if (check_in_out(str) == -1)
        {
            return -1;
        }
        *var_num += 1;
        if (*var_num > 99)
        {
            return -1;
        }
        fprintf(output, "%d READ %d \n", sa_line, *var_num);
        letters[str[0] - 'A'] = *var_num;
        lines[1][sb_line] = sa_line;
        break;

    case KEYW_OUTPUT:
        if (check_in_out(str) == -1)
            return -1;
        if (check_letter_cell(str[0], letters) == -1)
            return -1;
        fprintf(output, "%d WRITE %d \n", sa_line, letters[*str - 'A']);
        lines[1][sb_line] = sa_line;
        break;

    case KEYW_GOTO: {
        int cell = check_goto(str, lines);
        if (cell == -1)
        {
            return -1;
        }
        fprintf(output, "%d JUMP %d \n", sa_line, cell);
        lines[1][sb_line] = sa_line;
        break;
    }

    case KEYW_IF:
        break;

    case KEYW_LET:
        break;

    case KEYW_END:
        fprintf(output, "%d HALT 00 \n", sa_line);
        for (int i = 0; i < ALPHABET; i++)
        {
            if (letters[i] != -1)
            {
                fprintf(output, "%d = +1234 \n", letters[i]);
            }
        }
        lines[1][sb_line] = sa_line;
        break;

    default:
        break;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    char keyw_str[MAXLINES], line[MAXLINES];
    FILE *input, *output;
    int line_num = 0; //Номер строки
    int var_num = 89; //Хранение переменных в памяти (89-99)
    int keyw; //Операция (второй аргумент sb)
    int letters[ALPHABET]; //Объявленные переменные
    int line_index; //Индекс строки (первый аргумент sb)
    int sb_to_sa_lines[2][MAXLINES]; //Соответствие номера строки sb первой строке sa

    for (int i = 0; i < ALPHABET; i++)
    {
        letters[i] = -1;
    }
    for (int i = 0; i < MAXLINES; i++)
    {
        sb_to_sa_lines[0][i] = -1;
        sb_to_sa_lines[1][i] = -1;
    }

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
        //После get_tokens, в line остаётся последний токен - параметры
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

        keyw = get_keyword_code(keyw_str);

        if (keyw == -1)
        {
            fprintf(output, "Ошибка программы\n");
            return -1;
        }

        sb_to_sa_lines[0][line_num] = line_index;

        if (check_line_indexes(line_num, sb_to_sa_lines[0]) == -1)
        {
            fprintf(output, "Ошибка программы\n");
            return -1;
        }

        if (parsing(sb_to_sa_lines, line_num, &var_num, keyw, line, letters, output) == -1)
        {
            fprintf(output, "Ошибка программы\n");
            return -1;
        }
        if (keyw == KEYW_END)
        {
            return 1;
        }

        line_num++;
    }

    fclose(input);
    fclose(output);
    return 0;
}