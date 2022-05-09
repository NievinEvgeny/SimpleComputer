#pragma once

#define EMPTY_STR 1
#define ERR_ARG1 -1
#define ERR_ARG2 -2
#define ERR_ARG3 -3
#define ERR_FEW -4
#define ERR_MANY -5

int arg2_assign(char* str, int* value);

int arg2_command(char* str);

int pars_line(char* str, int* addr, int* value);

void print_error(char* line, int line_cnt, int err);

int chack_argv(char* argv[]);

int main(int argc, char* argv[]);