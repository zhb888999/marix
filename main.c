#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

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

void *create_data(size_t size, dtype type, void* init)
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

array *create_array(int *shape, int ndim, dtype type)
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
    array *arr = create_array(shape, ndim, type);
    if(!arr) return arr;
    arr->data = create_data(arr->size, type, value);
    if(!arr->data) free(arr);
    return arr;
}

array *ones(int *shape, int ndim, dtype type)
{
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

array *zeros(int *shape, int ndim, dtype type)
{
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

void free_array(array *arr)
{
	free(arr->data);
	free(arr->shape);
	free(arr);
}

char *print_dim(int size, int dim, int ndim, size_t *rep_count, size_t *str_size)
{
	assert(dim > 0 && dim <= ndim);
	char *str = (char *)malloc(size*(2+ndim));
	if(!str) return str;
	char *p = str;
	*rep_count = 0;
	*str_size = 0;

	for(int i=0; i<size; i++) {
		if(0==i) {
			*(p++) = '[';
			(*str_size) ++;
		} else if(i < size) {
			if(ndim==dim) {
				*(p++) = ' ';*(p++) = ',';
				(*str_size) +=2;
			} else {
				*(p++) = ',';
				(*str_size) ++;
				for(int j=0; j < ndim-dim; j++) {
					*(p++) = '\n';
					(*str_size) ++; 
				}
				for(int j=0; j < dim; j++) {
					*(p++) = ' ';
					(*str_size) ++; 
				}
			}
		}
		*(p++) = '#';
		(*rep_count) ++;
		(*str_size) ++; 
		if(i == size-1) {
			*(p++)=']';
			(*str_size) ++; 
		}
	}
	*p = '\0';
	return str; 
}

char *print_replace_dim(char *dst, char *src, size_t dst_rep_count, size_t dst_str_size, size_t src_rep_count, size_t src_str_size, size_t *rep_count, size_t *str_size)
{
	assert(dst && src);
	*str_size = dst_str_size - dst_rep_count + dst_rep_count * src_str_size + 1;
	*rep_count = src_rep_count * dst_rep_count;
	char *str = (char *)malloc(*str_size);
	char *p = str;
	if(!str) return str;
	for(size_t i=0; i<dst_str_size; i++) {
		if(*(dst+i) != '#') {
			*(p++) = *(dst+i);
			continue;
		}
		for(size_t j=0; j<src_str_size; j++) *(p++) = *(src+j);
	}
	*p = '\0';
	free(src);
	free(dst);
	return str;
}

char *print_data2string(char *data, dtype type, int data_width, int *final_width)
{
	int int32_width  = 5;
	int int64_width  = 5;
	int float_width  = 10;
	int double_width = 10;
	return 0;
}


char *print_replace_data(char *dst, void *data, size_t dst_rep_count, size_t dst_str_size, dtype type, int data_width) 
{
	return 0;
}

void print_array(array *arr)
{
	size_t dst_rep_count, dst_str_size, src_rep_count, src_str_size, rep_count, str_size;
	char *dst, *src, *str;
	int ndim = arr->ndim;
	for(int i=0; i < ndim; i++) {
		printf("%ld %ld\n", rep_count, str_size);
		if(0 == i) {
			dst = print_dim(arr->shape[i], i+1, ndim, &dst_rep_count, &dst_str_size);
			if(!dst) return;
			continue;
		}
		src = print_dim(arr->shape[i], i+1, ndim, &src_rep_count, &src_str_size);
		if(!src) {free(dst); return;}
		str = print_replace_dim(dst, src, dst_rep_count, dst_str_size, src_rep_count, src_str_size, &rep_count, &str_size);
		if(!str) {free(dst); free(src);};
		dst = str;
		dst_rep_count = rep_count;
		dst_str_size = str_size;
	}
	if(str) printf("%s\n", str);
	free(str);
}

int main() {
	int shape[4] = {5, 5, 5, 5}, size;
	array *test = zeros(shape, 4, int64);
	if(!test) {
        printf("error!");
        exit(1);
    }
	print_array(test);
	free_array(test);
}

