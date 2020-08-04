#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "matrix.h"


ashape *acshape(int ndim, ...)
{
	int size;
	ashape *shape = malloc(sizeof(ashape));	
	if(!shape) return shape;
	shape->value = calloc(ndim, sizeof(int));
	shape->ndim = ndim;
	if(!shape->value) {
		free(shape);
		return 0;
	}
	va_list ap;
	va_start(ap, ndim);
	for(int i = 0, *p=shape->value; i < ndim; i++, p++) {
		*p = va_arg(ap, int);
		if(*p < -1 || *p == 0) {
			free(shape->value);
			free(shape);
			return 0;
		}
	}
	return shape;
}

ashape *ashape_copy(ashape *shape)
{
	int size;
	ashape *new_shape = malloc(sizeof(ashape));	
	if(!new_shape) return new_shape;
	new_shape->value = calloc(shape->ndim, sizeof(int));
	new_shape->ndim = shape->ndim;
	if(!shape->value) {
		free(new_shape);
		return 0;
	}
	for(int i = shape->ndim; i < shape->ndim; i++)
		new_shape->value[i] = shape->value[i];
	return shape;
}

void asfree(ashape *shape)
{
	if(!shape) return;
	if(shape->value) free(shape->value);
	free(shape);
}


void _aidata(array *arr, void* init)
{
	size_t i, size=arr->size;
	void *data = arr->data;
	switch (arr->type) {
		case uint8:
            if(data && init) for(i=0; i < size; i++) ((uint8_t*)data)[i] = *(uint8_t*)init;
            return;
		case uint16:
            if(data && init) for(i=0; i < size; i++) ((uint16_t*)data)[i] = *(uint16_t*)init;
            return;
		case uint32:
            if(data && init) for(i=0; i < size; i++) ((uint32_t*)data)[i] = *(uint32_t*)init;
            return;
		case uint64:
            if(data && init) for(i=0; i < size; i++) ((uint64_t*)data)[i] = *(uint64_t*)init;
            return;
		case int8:
            if(data && init) for(i=0; i < size; i++) ((int8_t*)data)[i] = *(int8_t*)init;
            return;
		case int16:
            if(data && init) for(i=0; i < size; i++) ((int16_t*)data)[i] = *(int16_t*)init;
            return;
		case int32:
            if(data && init) for(i=0; i < size; i++) ((int32_t*)data)[i] = *(int32_t*)init;
            return;
		case int64:
            if(data && init) for(i=0; i < size; i++) ((int64_t*)data)[i] = *(int64_t*)init;
            return;
		case float32:
            if(data && init) for(i=0; i < size; i++) ((float*)data)[i] = *(float*)init;
            return;
		case float64:
            if(data && init) for(i=0; i < size; i++) ((double*)data)[i] = *(double*)init;
            return;
		default:
			fputs("dtype error!\n", stderr);
			return;
	}
}

void *acdata(size_t size, dtype type)
{
	switch (type) {
		case uint8:
			return calloc(size, sizeof(uint8_t));
		case uint16:
			return calloc(size, sizeof(uint16_t));
		case uint32:
			return calloc(size, sizeof(uint32_t));
		case uint64:
			return calloc(size, sizeof(uint64_t));
		case int8:
			return calloc(size, sizeof(int8_t));
		case int16:
			return calloc(size, sizeof(int16_t));
		case int32:
			return calloc(size, sizeof(int32_t));
		case int64:
			return calloc(size, sizeof(int64_t));
		case float32:
			return calloc(size, sizeof(float));
		case float64:
			return calloc(size, sizeof(double));
		default:
			fputs("dtype error!\n", stderr);
			break;
	}
	return 0;
}

array *acreate(ashape *shape, dtype type)
{
	if(!shape) return 0;
	array *arr = (array *)malloc(sizeof(array));
    if(!arr) return arr;
    arr->size = 1;
    arr->shape = ashape_copy(shape);
	if(!arr->shape) {
		free(arr);
		return 0;
	}
    arr->type = type;
	for(int i=0; i<arr->shape->ndim; i++) 
        arr->size *= shape->value[i];
	arr->data = acdata(arr->size, type);
	if(!arr->data) {
		asfree(arr->shape);
		free(arr);
		return 0;
	}
	return arr;
}

array *arepeat(ashape *shape, dtype type, void* value)
{
    array *arr = acreate(shape, type);
    if(!arr) return arr;
    _aidata(arr, value);
    return arr;
}

array *aones(ashape *shape, dtype type)
{
    void *value;
    uint8_t  v1 = 1;
    uint16_t v2 = 1;
    uint32_t v3 = 1;
    uint64_t v4 = 1;
    int8_t   v5 = 1;
    int16_t  v6 = 1;
    int32_t  v7 = 1;
    int64_t  v8 = 1;
    float    v9 = 1.0;
    double   v10 = 1.0;
    switch(type) {
        case uint8:
            value = &v1;
            break;
        case uint16:
            value = &v2;
            break;
        case uint32:
            value = &v3;
            break;
        case uint64:
            value = &v4;
            break;
        case int8:
            value = &v5;
            break;
        case int16:
            value = &v6;
            break;
        case int32:
            value = &v7;
            break;
        case int64:
            value = &v8;
            break;
        case float32:
            value = &v9;
            break;
        case float64:
            value = &v10;
            break;
        default:
            return 0;
    }
	return arepeat(shape, type, value);
}

array *azeros(ashape *shape, dtype type)
{
    void *value;
    uint8_t  v1 = 0;
    uint16_t v2 = 0;
    uint32_t v3 = 0;
    uint64_t v4 = 0;
    int8_t   v5 = 0;
    int16_t  v6 = 0;
    int32_t  v7 = 0;
    int64_t  v8 = 0;
    float    v9 = 0.0;
    double   v10 = 0.0;
    switch(type) {
        case uint8:
            value = &v1;
            break;
        case uint16:
            value = &v2;
            break;
        case uint32:
            value = &v3;
            break;
        case uint64:
            value = &v4;
            break;
        case int8:
            value = &v5;
            break;
        case int16:
            value = &v6;
            break;
        case int32:
            value = &v7;
            break;
        case int64:
            value = &v8;
            break;
        case float32:
            value = &v9;
            break;
        case float64:
            value = &v10;
            break;
        default:
            return 0;
    }
	return arepeat(shape, type, value);
}

void afree(array *arr)
{
	if(!arr) return;
    if(arr->data) free(arr->data);
	if(arr->shape) asfree(arr->shape);
	if(arr) free(arr);
}

int areshape(array *arr, ashape* new_shape)
{
    va_list ap;
    size_t new_size = 1;
    int dim = -1;
    ashape *shape = ashape_copy(new_shape);
    if(!new_shape) return -1;
    for(int i = 0, *p = shape->value; i < shape->ndim; i++, p++) {
        if(*p == 0 || *p < -1) goto err;
        if(-1 == *p) {
            if(-1 != dim) goto err;
            dim = i; continue;
        }
        new_size *= *p;
    }
    if(-1 != dim) {
        if(arr->size % new_size) goto err;
        shape->value[dim] = arr->size/new_size;
        new_size *= shape->value[dim];
    }
    if(new_size != arr->size) goto err;
    free(arr->shape);
    arr->shape = shape;
    return 0;
err:
    asfree(shape);
    return -1;
}

array *arange_uint8(uint8_t start, uint8_t end, uint8_t step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    uint8_t dis = end - start ? end - start : start - end;
    uint8_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, uint8);
    if(!arr) { asfree(shape); return 0; }
    uint8_t *p = (uint8_t *)arr->data;
    if(!arr->data) {afree(arr); return 0;}
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

array *arange_uint16(uint16_t start, uint16_t end, uint16_t step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    uint16_t dis = end - start ? end - start : start - end;
    uint16_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, uint16);
    if(!arr) { asfree(shape); return 0; }
    uint16_t *p = (uint16_t *)arr->data;
    if(!arr->data) {afree(arr); return 0;}
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

array *arange_uint32(uint32_t start, uint32_t end, uint32_t step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    uint32_t dis = end - start ? end - start : start - end;
    uint32_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, uint32);
    if(!arr) { asfree(shape); return 0; }
    uint32_t *p = (uint32_t *)arr->data;
    if(!arr->data) {afree(arr); return 0;}
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

array *arange_uint64(uint64_t start, uint64_t end, uint64_t step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    uint64_t dis = end - start ? end - start : start - end;
    uint64_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, uint32);
    if(!arr) { asfree(shape); return 0; }
    uint64_t *p = (uint64_t *)arr->data;
    if(!arr->data) {afree(arr); return 0;}
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}
array *arange_int8(int8_t start, int8_t end, int8_t step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    int8_t dis = end - start ? end - start : start - end;
    int8_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, int8);
    if(!arr) { asfree(shape); return 0; }
    int8_t *p = (int8_t *)arr->data;
    if(!arr->data) {afree(arr); return 0;}
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

array *arange_int16(int16_t start, int16_t end, int16_t step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    int16_t dis = end - start ? end - start : start - end;
    int16_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, int16);
    if(!arr) { asfree(shape); return 0; }
    int16_t *p = (int16_t *)arr->data;
    if(!arr->data) {afree(arr); return 0;}
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

array *arange_int32(int32_t start, int32_t end, int32_t step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    int32_t dis = end - start ? end - start : start - end;
    int32_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, int32);
    if(!arr) { asfree(shape); return 0; }
    int32_t *p = (int32_t *)arr->data;
    if(!arr->data) {afree(arr); return 0;}
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

array *arange_int64(int64_t start, int64_t end, int64_t step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    int64_t dis = end - start ? end - start : start - end;
    int64_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, int64);
    if(!arr) { asfree(shape); return 0; }
    int64_t *p = (int64_t *)arr->data;
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

array *arange_float32(float start, float end, float step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    float dis = end - start ? end - start : start - end;
    float abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, float32);
    if(!arr) { asfree(shape); return 0; }
    float *p = (float *)arr->data;
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

array *arange_float64(double start, double end, double step)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    double dis = end - start ? end - start : start - end;
    double abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
	ashape *shape = acshape(1, size);
	if(!shape) return 0;
    array *arr = acreate(shape, float64);
    if(!arr) { asfree(shape); return 0; }
    double *p = (double *)arr->data;
	for(size_t i=0; i < size; i++) *(p++) = start + step*i;
    return arr;
}

