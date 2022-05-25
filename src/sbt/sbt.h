#pragma once

#include <stdio.h>

#define MAXLINES 256
#define ALPHABET 26
#define MEMSIZE 100

enum keywords { KEYW_REM = 1, KEYW_INPUT = 2, KEYW_OUTPUT = 3, KEYW_GOTO = 4, KEYW_IF = 5, KEYW_LET = 6, KEYW_END = 7 };

typedef struct Stack_tag
{
    int data[MEMSIZE];
    size_t size;
} Stack_t;

int check_argv(char* argv[]);

int check_line_indexes(int line_num, int lines[MAXLINES]);

int get_tokens(char* line, int* line_index, char* keyword);

int get_keyword_code(char* str);

int check_in_out(char* str);

int check_goto(char* str, int lines[2][MAXLINES]);

int sa_start_line(int lines[2][MAXLINES], int sb_line);

int check_letter_cell(char cell, int* letters);

int if_get_cell(int* sa_line, int* var_num, int memory_nums[MEMSIZE], char* str, int* letters, FILE* output);

int if_jump_other_oper(
        int* sa_line,
        int lines[2][MAXLINES],
        int sb_line,
        int* var_num,
        int memory_nums[MEMSIZE],
        int key_if,
        char* str_if,
        int* letters,
        FILE* output);

int s_push(Stack_t* stack, const int value);

int s_pop(Stack_t* stack);

int s_peek(const Stack_t* stack);

int parsing_rpn(char* rpn, int answer_cell, int* sa_line, int* letters, FILE* output);

int parsing(int lines[2][MAXLINES], int sb_line, int* var_num, int memory_nums[MEMSIZE], int key, char* str, int* letters, FILE* output);

int main(int argc, char* argv[]);