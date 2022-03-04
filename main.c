#include "SimpleComputer.h"
#include "interface.h"
#include "myBigChar.h"
#include "myTerm.h"
#include <stdio.h>
#include <stdlib.h>

void printMenu()
{
    printf("1. Очистка экрана\n");
    printf("2. Перемещение курсора на (10, 1000)\n");
    printf("3. Размер экрана\n");
    printf("4. Цвет выводимого текста\n");
    printf("5. Цвет фона\n");
    printf("6. Выход\n");
}

int main()
{
    /*
    sc_memoryInit();
    sc_regInit();
    int value, command, operand;
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        sc_commandEncode(rand() % 76, rand() % 126, &value);
        sc_memorySet(i, value);
        printf("%d\n", Memory[i]);
    }
    printf("\n");
    sc_memorySave((char*)"doc");
    sc_memoryLoad((char*)"doc");
    sc_commandDecode(Memory[99], &command, &operand);
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        printf("%d\n", Memory[i]);
    }
    sc_memoryGet(1, &value);
    printf("value = %d", value);
    */
    /*
    int item = -1, rows = 0, cols = 0, color;
    while (item != 6)
    {
        // printMenu();
        scanf("%d", &item);
        switch (item)
        {
        case 1:
            mt_clrscr();
            break;
        case 2:
            mt_gotoXY(10, 10);
            break;
        case 3:
            mt_getscreensize(&rows, &cols);
            printf("rows = %d, cols = %d\n", rows, cols);
            break;
        case 4:
            printf("Введите цвет текста 0-7: ");
            scanf("%d", &color);
            mt_setfgcolor(color);
            break;
        case 5:
            printf("Введите цвет фона 0-7: ");
            scanf("%d", &color);
            mt_setbgcolor(color);
            break;
        }
    }
    */

    int value1;
    printf("///////////////////////\n");
    bc_printA("ascii = pepega\n");
    printf("///////////////////////\n");
    bc_box(5, 5, 10, 10);
    printf("///////////////////////\n");
    bc_setbigcharpos(bcAll[4], 5, 5, 0);
    bc_getbigcharpos(bcAll[4], 5, 4, &value1);
    printf("value = %d\n", value1);
    printf("///////////////////////\n");
    bc_printbigchar(bcAll[4], 1, 13, 4, 0);

    return 0;
}