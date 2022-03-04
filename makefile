all: myBigChar.c myTerm.c SimpleComputer.c main.c interface.c
		gcc -Wall -o bin $^
clean:
		rm bin doc