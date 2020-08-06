#include "print.h"
#include <stdint.h>
#include <stdio.h>


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

int ftoa(double num, char *buf)
{
	int i;
	sprintf(buf, "%g", num);
	for(i = 0; *(buf+i) != '\0'; i++){}
	return i;
}


void _apdata(array *arr, size_t data_index, int data_width)
{
    char buff[50];
	int len = 0;
    switch(arr->type) {
        case uint8:
			len = uitoa(*((uint8_t *)arr->data + data_index), buff);
            break;
        case uint16:
			len = uitoa(*((uint16_t *)arr->data + data_index), buff);
            break;
        case uint32:
			len = uitoa(*((uint32_t *)arr->data + data_index), buff);
            break;
        case uint64:
			len = uitoa(*((uint64_t *)arr->data + data_index), buff);
            break;
        case int8:
			len = itoa(*((int8_t *)arr->data + data_index), buff);
            break;
        case int16:
			len = itoa(*((int16_t *)arr->data + data_index), buff);
            break;
        case int32:
			len = itoa(*((int32_t *)arr->data + data_index), buff);
            break;
        case int64:
			len = itoa(*((int64_t *)arr->data + data_index), buff);
            break;
        case float32:
			len = ftoa(*((float *)arr->data + data_index), buff);
            break;
        case float64:
			len = ftoa(*((double *)arr->data + data_index), buff);
            break;
        default:
            break;
    }
    for(int i = 0; i < data_width - len; i++) fputc(' ', stdout);
    fputs(buff, stdout);
    
}

void _aprint(array *arr, int dim, size_t *data_index, int is_jmp, int data_width)
{
	if(!arr) return;
	int ndim = arr->shape->ndim;
    if (dim > ndim) return;

    int jmp = 1;
    char buf[30];
    int dim_size;
    if(arr->slice) {
        dim_size = arr->slice->end[dim-1] - arr->slice->start[dim-1];
        *data_index += arr->slice->start[dim-1] * arr->shape->step[dim-1];
    } else {
        dim_size = arr->shape->value[dim-1];
    }

	for(int i = 0; i < dim_size; i++) {
		if(0 == i) {
            /* first dim */
			fputc('[', stdout);
		} else if(i < dim_size) {
			if(ndim==dim) {
                /* last dim */
                fputs(", ", stdout);
			} else {
                /* others dim */
				fputc(',', stdout);
				for(int j=0; j < ndim-dim; j++) fputc('\n', stdout);
				for(int j=0; j < dim; j++) fputc(' ', stdout);
			}
		}
        if(is_jmp && dim_size > 6 && (i >= 3 && i < dim_size - 3)) {
            /* data size greater than 1000 and dim size greater than 6 jmp print */ 
            fputs("...", stdout);
            jmp *= arr->shape->step[dim-1];
            (*data_index) += jmp * (dim_size - 6);
            i += dim_size - 7;
        } else {
            /* not jmp */
            if(dim == ndim) {
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
    if(arr->slice)
        *data_index += (arr->shape->value[dim-1] - arr->slice->end[dim-1]) * arr->shape->step[dim-1];
}

void apinf(array *arr)
{
    if(!arr) return;
    if(arr->slice) {
        fputs("<slice ", stdout);
    } else {
        fputs("<array ", stdout);
    }
    int *value = arr->shape->value;
    int ndim = arr->shape->ndim;
    if(arr->slice) {
        int *start = arr->slice->start;
        int *end = arr->slice->end;
        for(int i=0; i <ndim - 1; i++) 
            fprintf(stdout, "%dx", end[i] - start[i]);
        fprintf(stdout, "%d ", end[ndim-1] - start[ndim-1]);
    } else {
        for(int i=0; i < ndim - 1; i++) 
            fprintf(stdout, "%dx", value[i]);
        fprintf(stdout, "%d ", value[ndim-1]);
    }
	switch (arr->type) {
		case uint8:
			fputs("uint8", stdout);
			break;
		case uint16:
			fputs("uint16", stdout);
			break;
		case uint32:
			fputs("uint32", stdout);
			break;
		case uint64:
			fputs("uint64", stdout);
			break;
		case int8:
			fputs("int8", stdout);
			break;
		case int16:
			fputs("int16", stdout);
			break;
		case int32:
			fputs("uint32", stdout);
			break;
		case int64:
			fputs("uint64", stdout);
			break;
		case float32:
			fputs("float32", stdout);
			break;
		case float64:
			fputs("float64", stdout);
			break;
		default:
			fputs("undefine", stdout);
			break;
	}
    fputs(">\n", stdout);
}


int _apdwidth(array *arr)
{
    char buff[50];
	int width = 0;
    int len = 0;
	int max_width = 0;
	int min_width = 0;
	switch (arr->type) {
		case uint8:
			max_width = itoa(*((uint8_t *)arr->data + amax(arr)), buff);
			min_width = itoa(*((uint8_t *)arr->data + amin(arr)), buff);
			break;
		case uint16:
			max_width = itoa(*((uint16_t *)arr->data + amax(arr)), buff);
			min_width = itoa(*((uint16_t *)arr->data + amin(arr)), buff);
			break;
		case uint32:
			max_width = itoa(*((uint32_t *)arr->data + amax(arr)), buff);
			min_width = itoa(*((uint32_t *)arr->data + amin(arr)), buff);
			break;
		case uint64:
			max_width = itoa(*((uint64_t *)arr->data + amax(arr)), buff);
			min_width = itoa(*((uint64_t *)arr->data + amin(arr)), buff);
			break;
		case int8:
			max_width = itoa(*((int8_t *)arr->data + amax(arr)), buff);
			min_width = itoa(*((int8_t *)arr->data + amin(arr)), buff);
			break;
		case int16:
			max_width = itoa(*((int16_t *)arr->data + amax(arr)), buff);
			min_width = itoa(*((int16_t *)arr->data + amin(arr)), buff);
			break;
		case int32:
			max_width = itoa(*((int32_t *)arr->data + amax(arr)), buff);
			min_width = itoa(*((int32_t *)arr->data + amin(arr)), buff);
			break;
		case int64:
			max_width = itoa(*((int64_t *)arr->data + amax(arr)), buff);
			min_width = itoa(*((int64_t *)arr->data + amin(arr)), buff);
			break;
		case float32:
			max_width = ftoa(*((float *)arr->data + amax(arr)), buff);
			min_width = ftoa(*((float *)arr->data + amin(arr)), buff);
			break;
		case float64:
			max_width = ftoa(*((double *)arr->data + amax(arr)), buff);
			min_width = ftoa(*((double *)arr->data + amin(arr)), buff);
			break;
		default:
			fputs("undefine", stdout);
			break;
	}
    width = min_width < max_width ? max_width : min_width;
	return width;
}

void aprint(array *arr)
{
    size_t data_index = 0;
    _aprint(arr, 1, &data_index, arr->slice ? arr->slice->size > 1000 : arr->size > 1000, _apdwidth(arr));
    fputc('\n', stdout);
    apinf(arr);
}
