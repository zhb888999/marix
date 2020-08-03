run: matrix 
	./matrix
matrix: main.c matrix.h matrix.o print.o
	gcc main.c -o matrix matrix.o print.o
matrix.o: matrix.c
	gcc matrix.c -c -o matrix.o
print.o: print.c print.h
	gcc print.c -c -o print.o

