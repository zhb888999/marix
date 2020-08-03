#ifndef PRINT_H
#define PRINT_H

#include "matrix.h"

int itoa(int64_t num, char *buf);
int uitoa(uint64_t num, char *buf);
int ftoa(double num, char *buf);
int _apdwidth(array *arr);
void _aprint(array *arr, int dim, size_t *data_index, int is_jmp, int data_width);
void _apdata(array *arr, size_t data_index, int data_width);

#endif

