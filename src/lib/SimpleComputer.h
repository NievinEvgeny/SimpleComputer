#pragma once

#define MEMORY_SIZE 100

#define CHECK_BIT(reg, flag) (((reg) >> flag) & 1)

#define P 1 //переполнение при выполнении операции
#define O 2 //ошибка деления на 0
#define M 3 //ошибка выхода за границы памяти
#define T 4 //игнорирование тактовых импульсов
#define E 5 //указана неверная команда

extern int registr;
extern int Memory[MEMORY_SIZE];
extern int accumulator;
extern int instructionCounter;

void sc_memoryInit();

int sc_memorySet(int, int);

int sc_memoryGet(int, int*);

int sc_memorySave(char* s);

int sc_memoryLoad(char* s);

void sc_regInit();

int sc_regSet(int, int);

int sc_regGet(int Flags, int* value);

int sc_commandEncode(int, int, int*);

int sc_commandDecode(int, int*, int*);

void Print();