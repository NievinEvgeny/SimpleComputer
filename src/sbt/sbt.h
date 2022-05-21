#pragma once

enum keywords { KEYW_REM = 1, KEYW_INPUT = 2, KEYW_OUTPUT = 3, KEYW_GOTO = 4, KEYW_IF = 5, KEYW_LET = 6, KEYW_END = 7 };

int check_argv(char* argv[]);

int get_tokens(char* line, int* line_index, char* keyword);

int get_keyword_code(char* str);

int main(int argc, char* argv[]);