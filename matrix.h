#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdint.h>

enum dtype {
	uint8,
	uint16,
	uint32,
	uint64,
	int8,
	int16,
	int32,
	int64,
	float32,
	float64,
};
typedef enum dtype dtype;

struct ashape {
	int *value;
	int ndim;
};
typedef struct ashape ashape;

struct array {
	void *data;
	ashape *shape;
	size_t size;
	dtype type;
};
typedef struct array array;

ashape *acshape(int ndim, ...);
ashape *ashape_copy(ashape *shape);
void asfree(ashape *shape);
array *acreate(ashape *shape, dtype type);
void afree(array *arr);
array *aones(ashape *shape, dtype type);
array *azeros(ashape *shape, dtype type);
int areshape(array *arr, ashape* new_shape);
array *arange(int64_t start, int64_t end, int64_t step,  dtype type);
void apinf(array *arr);
void aprint(array *arr);
size_t amax(array *arr);
size_t amin(array *arr);

#endif
