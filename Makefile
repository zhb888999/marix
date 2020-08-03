run: matrix
	./matrix
matrix: main.c
	gcc main.c -o matrix

