#ifndef CALCULATE_H
#define CALCULATE_H

#include "matrix.h"

struct message {
	void *data;
	size_t size;
	dtype type;
	void *value;
};

void pcmax(void *mess);
void amax(array *arr, void *value);
void amin(array *arr, void *value);

#endif
