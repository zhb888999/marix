run: matrix 
	./matrix
matrix: main.c matrix.h matrix.o print.o calculate.o range.o
	gcc main.c -pthread -o matrix matrix.o print.o calculate.o
matrix.o: matrix.c
	gcc matrix.c -c -o matrix.o
print.o: print.c print.h
	gcc print.c -c -o print.o
calculate.o:  calculate.c calculate.h
	gcc calculate.c -c -lpthread -o calculate.o
range.o: range.c
	gcc range.c -c -o range.o
clean:
	rm *.o
	rm matrix

