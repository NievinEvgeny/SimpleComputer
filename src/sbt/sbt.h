#pragma once

enum keywords { KEYW_REM = 1, KEYW_INPUT = 2, KEYW_OUTPUT = 3, KEYW_GOTO = 4, KEYW_IF = 5, KEYW_LET = 6, KEYW_END = 7 };

int check_argv(char* argv[]);

int get_tokens(char* line, int* line_index, char* keyword);

int get_keyword_code(char* str);

int check_in_out(char* str);

int sa_start_line(int lines[2][MAXLINES], int sb_line);

int check_letter_cell(char cell, int* letters);

int parsing(int lines[2][MAXLINES], int sb_line, int* var_num, int key, char* str, int* letters, FILE* output);

int main(int argc, char* argv[]);