#include "myReadKey.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int rk_readkey(enum keys* key)
{
    char buf[16];
    int num_read;

    if (rk_mytermregime(0, 0, 1, 1, 1) != 0)
    {
        return -1;
    }

    num_read = read(STDIN_FILENO, buf, 15);

    if (num_read < 0)
    {
        return -1;
    }

    buf[num_read] = '\0';

    if (strcmp(buf, "l") == 0)
        *key = KEY_l;
    else if (strcmp(buf, "s") == 0)
        *key = KEY_s;
    else if (strcmp(buf, "r") == 0)
        *key = KEY_r;
    else if (strcmp(buf, "t") == 0)
        *key = KEY_t;
    else if (strcmp(buf, "i") == 0)
        *key = KEY_i;
    else if (strcmp(buf, "q") == 0)
        *key = KEY_q;
    else if (strcmp(buf, "\n") == 0)
        *key = KEY_enter;
    else if (strcmp(buf, "\033[15~") == 0)
        *key = KEY_f5;
    else if (strcmp(buf, "\033[17~") == 0)
        *key = KEY_f6;
    else if (strcmp(buf, "\033[A") == 0)
        *key = KEY_up;
    else if (strcmp(buf, "\033[B") == 0)
        *key = KEY_down;
    else if (strcmp(buf, "\033[C") == 0)
        *key = KEY_right;
    else if (strcmp(buf, "\033[D") == 0)
        *key = KEY_left;
    else
        *key = KEY_other;

    return 0;
}

int rk_mytermsave()
{
    struct termios options;
    FILE* file;

    if (tcgetattr(TCSANOW, &options) != 0)
    {
        return -1;
    }
    if ((file = fopen("termsettings", "wb")) == NULL)
    {
        return -1;
    }
    fwrite(&options, sizeof(options), 1, file);
    fclose(file);

    return 0;
}

int rk_mytermrestore()
{
    struct termios options;
    FILE* file;

    if ((file = fopen("termsettings", "rb")) == NULL)
    {
        return -1;
    }
    if (fread(&options, sizeof(options), 1, file) <= 0)
    {
        return -1;
    }
    if (tcsetattr(TCSANOW, TCSAFLUSH, &options) != 0)
    {
        return -1;
    }

    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    // ECHO - отображать вводимые символы
    // VTIME - Время ожидания в децисекундах для неканонического ввода
    // VMIN - Минимальное количество символов для неканонического ввода

    struct termios options;

    if (tcgetattr(TCSANOW, &options) != 0)
    {
        return -1;
    }

    if (regime == 1) //Канонический режим
    {
        options.c_lflag |= ICANON;
    }
    else if (regime == 0) //Неканонический режим
    {
        options.c_lflag &= ~ICANON;
        options.c_cc[VTIME] = vtime;
        options.c_cc[VMIN] = vmin;

        if (echo == 1)
        {
            options.c_lflag |= ECHO;
        }
        else if (echo == 0)
        {
            options.c_lflag &= ~ECHO;
        }
        else
        {
            return -1;
        }
        if (sigint == 1)
        {
            options.c_lflag |= ISIG;
        }
        else if (sigint == 0)
        {
            options.c_lflag &= ~ISIG;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }

    if (tcsetattr(TCSANOW, TCSANOW, &options) != 0)
    {
        return -1;
    }

    return 0;
}