#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "matrix.h"

size_t _setstep(ashape *shape,int dim)
{
	shape->step[dim-1] = dim == shape->ndim ? 1 : shape->value[dim] * _setstep(shape, dim+1);
	return shape->step[dim-1];
}

ashape *acshape(int ndim, ...)
{
	int size;
	ashape *shape = calloc(1, sizeof(ashape));	
	if(!shape) return shape;
	if(!(shape->value = calloc(ndim, sizeof(int)))) {
		free(shape);
		return 0;
	};
	if(!(shape->step = calloc(ndim, sizeof(size_t)))) {
		free(shape->value);
		free(shape);
		return 0;
	};
	shape->ndim = ndim;
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
	_setstep(shape, 1);
	return shape;
}

ashape *ashape_copy(ashape *shape)
{
	int size;
	ashape *new_shape;
    if(!(new_shape = calloc(1, sizeof(ashape))))
        return 0;	
	if(!(new_shape->value = calloc(shape->ndim, sizeof(int)))) {
        free(new_shape);
        return 0;
    };
	if(!(new_shape->step = calloc(shape->ndim, sizeof(size_t)))) {
        free(new_shape->value);
        free(new_shape);
        return 0;
    };
	new_shape->ndim = shape->ndim;
	for(int i = shape->ndim; i < shape->ndim; i++) {
		new_shape->value[i] = shape->value[i];
        new_shape->step[i] = shape->step[i];
    }
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
	array *arr;
    if(!(arr = calloc(1, sizeof(array))))
        return 0;
    if(!(arr->shape = ashape_copy(shape))) {
        free(arr);
        return 0;
    };
    arr->size = 1;
    arr->type = type;
	for(int i=0; i < arr->shape->ndim; i++) 
        arr->size *= shape->value[i];
    if(0 == arr->shape->ndim) {
        arr->size=0;
        return arr;
    }
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
    array *arr;
    if(!(arr = acreate(shape, type)))
        return 0;
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
    if(arr->slice) aslifree(arr->slice);
	if(arr) free(arr);
}

int areshape(array *arr, ashape* new_shape)
{
    va_list ap;
    size_t new_size = 1;
    int dim = -1;
    ashape *shape;
    if(!(shape = ashape_copy(new_shape))) 
        return -1;
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
    _setstep(shape, 1);
    arr->shape = shape;
    return 0;
err:
    asfree(shape);
    return -1;
}

size_t aindex(array *arr, ...)
{
	va_list ap;
	va_start(ap, arr);
	size_t index = 0;
	int dim_index;
    int *value = arr->shape->value;
    size_t *step = arr->shape->step;
    int ndim = arr->shape->ndim;
    /* slice */
    if(!arr->slice) {
        for(int i=0; i < ndim; i++) {
            dim_index = va_arg(ap, int);
            if(dim_index > *(value++)) 
                return -1;
            index += dim_index*(*(step++));
        }
        return index;
    }
    /* array */
    int *start = arr->slice->start;
    int *end = arr->slice->end;
    for(int i=0; i < ndim; i++) {
        dim_index = va_arg(ap, int) + *(start++);
        if(dim_index > *(end++)) 
            return -1;
        index += dim_index*(*(step++));
    }
    return index;
}

void avalue(void *value, array *arr, ...)
{
	if(!arr) return;
    va_list ap;
    va_start(ap , arr);
    size_t index;
    if((index = aindex(arr, ap) == -1))
        return;
    va_end(ap);
    switch(arr->type) {
        case uint8:
            *(uint8_t *)value = *((uint8_t *)arr->data + index);
            return;
        case uint16:
            *(uint16_t *)value = *((uint16_t *)arr->data + index);
            return;
        case uint32:
            *(uint32_t *)value = *((uint32_t *)arr->data + index);
            return;
        case uint64:
            *(uint64_t *)value = *((uint64_t *)arr->data + index);
            return;
        case int8:
            *(int8_t *)value = *((int8_t *)arr->data + index);
            return;
        case int16:
            *(int16_t *)value = *((int16_t *)arr->data + index);
            return;
        case int32:
            *(int32_t *)value = *((int32_t *)arr->data + index);
            return;
        case int64:
            *(int64_t *)value = *((int64_t *)arr->data + index);
            return;
        case float32:
            *(float *)value = *((float *)arr->data + index);
            return;
        case float64:
            *(double *)value = *((double *)arr->data + index);
            return;
        default:
            return;
    }
}

_slice *acslice(int ndim)
{
    _slice *slice = calloc(1, sizeof(slice));
    if(!slice) return 0;
    slice->start = calloc(ndim, sizeof(int));
    if(!slice->start) {
        free(slice);
        return 0;
    }
    slice->end = calloc(ndim, sizeof(int));
    if(!slice->end) {
        free(slice->start);
        free(slice);
    }
    return slice;
}

void aslifree(_slice * slice)
{
    if(!slice) return;
    if(slice->start) free(slice->start);
    if(slice->end) free(slice->end);
    free(slice);
}

void _anaslice(int *start, int *end, int dim_size)
{
    *start = *start >= 0 ? *start : dim_size + *start;
    *end = *end >= 0 ? *end : dim_size + *end;
    if(*start >= *end || *start >= dim_size || *start < 0)
        *start = *end = 0;
    *end = *end > dim_size ? dim_size : *end;
}


array *aslice(array *arr, ...)
{
    if(!arr) return 0;
    array *new_arr;
    if(!(new_arr = calloc(1, sizeof(array))))
        return 0;
    if(!(new_arr->slice = acslice(arr->shape->ndim))) {
        free(new_arr);
        return 0;
    }
    if(!(new_arr->shape = ashape_copy(arr->shape))) {
        aslifree(new_arr->slice);
        free(new_arr);
        return 0;
    }
    new_arr->type = arr->type;
    new_arr->data = arr->data;
    new_arr->size = arr->size;
    va_list ap;
    va_start(ap, arr);
    int *start, *end, *value;
    start = new_arr->slice->start;
    end = new_arr->slice->end;
    value = new_arr->shape->value;
    new_arr->slice->size = 1;
    for(int i=0; i < arr->shape->ndim; i++) {
        *(start++) = va_arg(ap, int);
        *(end++) = va_arg(ap, int);
        _anaslice(start, end, *(value++));
        new_arr->slice->size *= end-start;
    }
    if(0 == arr->shape->ndim)
        new_arr->slice->size = 0;
    return new_arr;
}
