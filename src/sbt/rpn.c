#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>

int check_brackets(char* str)
{
    int open = 0, close = 0;
    while (*str)
    {
        if (*str == '(')
        {
            open++;
        }
        if (*str == ')')
        {
            close++;
        }
        if (close > open)
        {
            return -1;
        }
        str++;
    }
    if (open == close)
    {
        return 0;
    }
    return -1;
}

int check_letters(char* str)
{
    int flag = 0;
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        if (!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9') && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/'
            && str[i] != ')' && str[i] != '(')
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

int is_oper(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ')' || ch == '\0' || ch == '\n')
    {
        return 1;
    }
    return 0;
}

int check_opers(char* str)
{
    if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/')
    {
        return -1;
    }
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(')
        {
            if (is_oper(str[i + 1]))
            {
                return -1;
            }
        }
    }
    return 0;
}

int check_exception(char* str)
{
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        if (str[i] == ')' && (str[i + 1] >= 'A' && str[i + 1] <= 'Z'))
        {
            return -1;
        }
        if ((str[i] >= 'A' && str[i] <= 'Z') && str[i + 1] == '(')
        {
            return -1;
        }
    }
    return 0;
}

void remove_spaces(char* str)
{
    char* i = str;
    char* j = str;
    while (*j != 0)
    {
        *i = *j++;
        if (*i != ' ')
        {
            i++;
        }
    }
    *i = 0;
}

struct stack_t* stack_push(struct stack_t* head, char letter)
{
    struct stack_t* ptr;
    ptr = malloc(sizeof(struct stack_t));
    ptr->ch = letter;
    ptr->next = head;
    return ptr;
}

char stack_pop(struct stack_t** head)
{
    struct stack_t* ptr;
    if (*head == NULL)
    {
        return '\0';
    }
    ptr = *head;
    *head = ptr->next;
    return ptr->ch;
}

int get_prior(char ch)
{
    switch (ch)
    {
    case '(':
        return 1;
    case '-':
    case '+':
        return 2;
    case '*':
    case '/':
        return 3;
    }
}

int translate_to_rpn(char* RPN, char* str)
{
    remove_spaces(str);
    if (str[0] == '\0')
        return -1;
    if (check_brackets(str) == -1)
        return -1;
    if (check_letters(str) == -1)
        return -1;
    if (check_opers(str) == -1)
        return -1;
    if (check_exception(str) == -1)
        return -1;

    struct stack_t* opers = NULL;
    int point = 0;

    for (int k = 0; str[k] != '\0' && str[k] != '\n'; k++)
    {
        if (str[k] == ')')
        {
            while ((opers->ch) != '(')
            {
                RPN[point++] = ' ';
                RPN[point++] = stack_pop(&opers);
                RPN[point++] = ' ';
            }
            stack_pop(&opers);
        }
        if (str[k] >= '0' && str[k] <= '9')
        {
            RPN[point++] = str[k];
        }
        if (str[k] >= 'A' && str[k] <= 'Z')
        {
            RPN[point++] = ' ';
            RPN[point++] = str[k];
            RPN[point++] = ' ';
        }
        if (str[k] == '(')
        {
            opers = stack_push(opers, '(');
        }
        if (str[k] == '+' || str[k] == '-' || str[k] == '/' || str[k] == '*')
        {
            if (opers == NULL)
            {
                opers = stack_push(opers, str[k]);
            }
            else if (get_prior(opers->ch) < get_prior(str[k]))
            {
                opers = stack_push(opers, str[k]);
            }
            else
            {
                while ((opers != NULL) && (get_prior(opers->ch) >= get_prior(str[k])))
                {
                    RPN[point++] = ' ';
                    RPN[point++] = stack_pop(&opers);
                    RPN[point++] = ' ';
                }
                opers = stack_push(opers, str[k]);
            }
        }
    }
    while (opers != NULL)
    {
        RPN[point++] = ' ';
        RPN[point++] = stack_pop(&opers);
        RPN[point++] = ' ';
    }
    RPN[point] = '\0';
    return 0;
}