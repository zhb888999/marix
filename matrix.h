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
	size_t *step;
	int ndim;
};
typedef struct ashape ashape;

struct array {
	ashape *shape;
	void *data;
	size_t size;
	dtype type;
    int *slice;
};
typedef struct array array;

ashape *acshape(int ndim, ...);
ashape *ashape_copy(ashape *shape);
void asfree(ashape *shape);

array *acreate(ashape *shape, dtype type);
void afree(array *arr);

array *aslice(array *arr, ...);

array *aones(ashape *shape, dtype type);
array *azeros(ashape *shape, dtype type);

int areshape(array *arr, ashape* new_shape);

void apinf(array *arr);
void aprint(array *arr);

size_t amax(array *arr);
size_t amin(array *arr);

array *arange_uint8(uint8_t start, uint8_t end, uint8_t step);
array *arange_uint16(uint16_t start, uint16_t end, uint16_t step);
array *arange_uint32(uint32_t start, uint32_t end, uint32_t step);
array *arange_uint64(uint64_t start, uint64_t end, uint64_t step);
array *arange_int8(int8_t start, int8_t end, int8_t step);
array *arange_int16(int16_t start, int16_t end, int16_t step);
array *arange_int32(int32_t start, int32_t end, int32_t step);
array *arange_int64(int64_t start, int64_t end, int64_t step);
array *arange_float32(float start, float end, float step);
array *arange_float64(double start, double end, double step);
array *arange(void *start, void *end, void *step, dtype type);

#endif
