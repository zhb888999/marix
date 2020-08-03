#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

enum dtype {
	int32,
	int64,
	float32,
	float64
};
typedef enum dtype dtype;

struct array {
	void *data;
	int ndim;
	int *shape;
	size_t size;
	dtype type;
};
typedef struct array array;


int itoa(int64_t num, char *buf)
{
    char stack[25];
    int i=-1;
    int c = INT64_MIN == num ? 1 : 0;
    int symbol = num < 0 ? 1 : 0;
    num = num > 0 ? num : -(num+c);
    *(stack+(++i)) = '\0';
    *(stack+(++i)) = num%10+48+c;
    while(num/=10) *(stack+(++i)) = num%10+48;
    if(symbol) *(stack+(++i)) = '-';
    for(int j=i; j >= 0; j--) *(buf++) = *(stack+j);
    return i;
}

int uitoa(uint64_t num, char *buf)
{
    char stack[25];
    int i=-1;
    *(stack+(++i)) = '\0';
    *(stack+(++i)) = num%10+48;
    while(num/=10) *(stack+(++i)) = num%10+48;
    for(int j=i; j >= 0; j--) *(buf++) = *(stack+j);
    return i;
}

void ftoa(double num, char *buf)
{
    union u_num{
        double num;
        struct {
            uint64_t mantissa:52;
            unsigned exp: 11;
            unsigned symbol: 1;
        } bits;
    };
    char stack[100];
    union u_num *unum = (union u_num *)&num;
    printf("%lf:%d %d %lu\n", num, unum->bits.symbol, unum->bits.exp, unum->bits.mantissa);
}

void *_acdata(size_t size, dtype type, void* init)
{
	size_t i;
	void *data;
	switch (type) {
		case int32:
			data = calloc(size, sizeof(int32_t));
            if(data && init) for(i=0; i < size; i++) ((int64_t*)data)[i] = *(int32_t*)init;
            return data;
		case int64:
			data = calloc(size, sizeof(int64_t));
            if(data && init) for(i=0; i < size; i++) ((int64_t*)data)[i] = *(int64_t*)init;
            return data;
		case float32:
			data = calloc(size, sizeof(float));
            if(data && init) for(i=0; i < size; i++) ((int64_t*)data)[i] = *(float*)init;
            return data;
		case float64:
			data = calloc(size, sizeof(double));
            if(data && init) for(i=0; i < size; i++) ((double*)data)[i] = *(double*)init;
            return data;
		default:
			return data;
	}
}

array *acreate(int *shape, int ndim, dtype type)
{
	array *arr = (array *)malloc(sizeof(array));
    if(!arr) return arr;
    arr->size = 1;
    arr->ndim = ndim;
    arr->type = type;
    arr->shape = calloc(ndim, sizeof(int));
	for(int i=0; i<ndim; i++) {
        arr->shape[i] = shape[i];
        arr->size *= shape[i];
    }
	return arr;
}

array *repeat(int *shape, int ndim, dtype type, void* value)
{
    array *arr = acreate(shape, ndim, type);
    if(!arr) return arr;
    arr->data = _acdata(arr->size, type, value);
    if(!arr->data) free(arr);
    return arr;
}

array *ones(dtype type, int ndim, ...)
{
    int *shape = calloc(ndim, sizeof(int));
    if(!shape) return 0;
    va_list ap;
    va_start(ap, ndim);
    for(int i = 0, *p = shape; i < ndim; i++, p++) {
        *p = va_arg(ap, int);
        if(*p < 1) {
            free(shape);
            va_end(ap);
            return 0;
        }
    }
    void *value;
    int32_t v1 = 1;
    int64_t v2 = 1;
    float v3 = 1.0;
    double v4 = 1.0;
    switch(type) {
        case int32:
            value = &v1;
            break;
        case int64:
            value = &v2;
            break;
        case float32:
            value = &v3;
            break;
        case float64:
            value = &v4;
            break;
        default:
            return 0;
    }
	return repeat(shape, ndim, type, value);
}

array *zeros(dtype type, int ndim, ...)
{
    int *shape = calloc(ndim, sizeof(int));
    if(!shape) return 0;
    va_list ap;
    va_start(ap, ndim);
    for(int i = 0, *p = shape; i < ndim; i++, p++) {
        *p = va_arg(ap, int);
        if(*p < 1) {
            free(shape);
            va_end(ap);
            return 0;
        }
    }
    void *value;
    int32_t v1 = 0;
    int64_t v2 = 0;
    float v3 = 0.0;
    double v4 = 0.0;
    switch(type) {
        case int32:
            value = &v1;
            break;
        case int64:
            value = &v2;
            break;
        case float32:
            value = &v3;
            break;
        case float64:
            value = &v4;
            break;
        default:
            return 0;
    }
	return repeat(shape, ndim, type, value);
}

void afree(array *arr)
{
    if(arr->data) free(arr->data);
	if(arr->shape) free(arr->shape);
	if(arr) free(arr);
}

void _apdata(array *arr, size_t data_index, int data_width)
{
    char buff[50];
    int len = itoa(*((int64_t *)arr->data+data_index), buff);
    for(int i = 0; i < data_width -len; i++) fputc(' ', stdout);
    fputs(buff, stdout);
    
}

void _aprint(array *arr, int dim, size_t *data_index, int is_jmp, int data_width)
{
    if (dim > arr->ndim) return;
    int dim_size = arr->shape[dim-1];
    int jmp = 1;
    char b[25];

	for(int i = 0; i < dim_size; i++) {
		if(0 == i) {
            /* first dim */
			fputc('[', stdout);
		} else if(i < dim_size) {
			if(arr->ndim==dim) {
                /* last dim */
                fputs(", ", stdout);
			} else {
                /* others dim */
				fputc(',', stdout);
				for(int j=0; j < arr->ndim-dim; j++) fputc('\n', stdout);
				for(int j=0; j < dim; j++) fputc(' ', stdout);
			}
		}
        if(is_jmp && dim_size > 6 && (i >= 3 && i < dim_size - 3)) {
            /* data size greater than 1000 and dim size greater than 6 jmp print */ 
            fputs("...", stdout);
            for(int z=dim; z < arr->ndim; z++) jmp *= arr->shape[z];
            (*data_index) += jmp * (dim_size - 6);
            i += dim_size - 7;
        } else {
            /* not jmp */
            if(dim == arr->ndim) {
                /* the last dim print data */
                _apdata(arr, *data_index, data_width);
                (*data_index)++;
            } else {
                /* print next dim */
                _aprint(arr, dim+1, data_index, is_jmp, data_width);
            }
        }
        /* dim end */
		if(i == dim_size-1) fputc(']', stdout);
	}
}

int reshape(array *arr, int new_ndim, ...)
{
    va_list ap;
    size_t new_size = 1;
    int dim = -1;
    int *new_shape = calloc(new_ndim, sizeof(int));
    if(!new_shape) return -1;
    va_start(ap, new_ndim);
    for(int i = 0, *p = new_shape; i < new_ndim; i++, p++) {
        *p = va_arg(ap, int);
        if(*p == 0 || *p < -1) {
            va_end(ap);
            goto err;
        }
        if(-1 == *p) {
            if(-1 != dim) {
                va_end(ap);
                goto err;
            }
            dim = i; continue;
        }
        new_size *= *p;
    }
    va_end(ap);
    if(-1 != dim) {
        if(arr->size%new_size) goto err;
        *(new_shape+dim) = arr->size/new_size;
        new_size *= *(new_shape+dim);
    }
    if(new_size != arr->size) goto err;
    free(arr->shape);
    arr->shape = new_shape;
    arr->ndim = new_ndim;
    return 0;
err:
    free(new_shape);
    return -1;
}

array *arange(int64_t start, int64_t end, int64_t step,  dtype type)
{
    if(0 == step || (start > end && 0 < step) || (start < end && 0 > step) || start == end) return 0;
    int64_t dis = end - start ? end - start : start - end;
    int64_t abs_step = step > 0 ? step : -step;
    ssize_t size = dis / abs_step;
    int shape[1] = {size};
    array *arr = acreate(shape, 1, type);
    if(!arr) return 0;
    arr->data = calloc(size, sizeof(int64_t));
    int64_t *p = (int64_t *)arr->data;
    if(!arr->data) {afree(arr); return 0;}
    char buf[25];
    if(step > 0) {
        for(;start < end; start += step) *(p++) = start;
    } else {
        for(;start > end; start += step) *(p++) = start;
    }
    return arr;
}

void _ainf(array *arr)
{
    fputs("<array ", stdout);
    for(int i=0; i < arr->ndim - 1; i++) fprintf(stdout, "%dx", arr->shape[i]);
    fprintf(stdout, "%d", arr->shape[arr->ndim-1]);
    fputs(">\n", stdout);
}

void aprint(array *arr)
{
    char buff[50];
    size_t data_index = 0;
	int width = 0;
    int len = 0;
	int max_width = 0;
	int min_width = 0;
    int64_t max = *((int64_t *)arr->data);
    int64_t min = *((int64_t *)arr->data);
    for(size_t i=0; i < arr->size; i++) {
        if(*((int64_t *)arr->data+i) > max) max = (*((int64_t *)arr->data+i));
        if(*((int64_t *)arr->data+i) < min) min = (*((int64_t *)arr->data+i));
    }
    max_width = itoa(max, buff);
    min_width = itoa(min, buff);
    width = min_width < max_width ? max_width : min_width;
    _aprint(arr, 1, &data_index, arr->size > 1000, width);
    fputc('\n', stdout);
    _ainf(arr);
}

int main() {
    array *test1 = ones(int64, 3, 11, 11, 9);
    aprint(test1);
    array *test2 = arange(0, 100000000, 1, int64);
    //reshape(test2, 2, 10, -1);
    aprint(test2);
    afree(test1);
    afree(test2);
}

