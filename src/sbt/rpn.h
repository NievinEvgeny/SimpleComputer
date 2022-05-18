#pragma once

struct stack_t
{
    char ch;
    struct stack_t* next;
};

int check_brackets(char* str);

int check_letters(char* str);

int is_oper(char ch);

int check_opers(char* str);

int check_exception(char* str);

void remove_spaces(char* str);

struct stack_t* stack_push(struct stack_t* head, char letter);

char stack_pop(struct stack_t** head);

int get_prior(char ch);

int translate_to_rpn(char* RPN, char* str);