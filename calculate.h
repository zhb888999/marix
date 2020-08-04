#ifndef CALCULATE_H
#define CALCULATE_H

#include "matrix.h"

#define USE_MULTHREAD_SIZE 100000

struct message {
	void *data;
	size_t size;
	dtype type;
	size_t index;
    size_t bindex;
};
typedef struct message message;

void *pcmax(void *mess);
void *pcmin(void *mess);
size_t amaxmin(array *arr, int max_min);

#endif
