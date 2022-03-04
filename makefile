all: myBigChar.c myTerm.c SimpleComputer.c main.c
		gcc -Wall -o bin $^
clean:
		rm bin doc