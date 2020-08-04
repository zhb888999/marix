#include "matrix.h"

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
    array *arr = acreate(shape, uint64);
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

array *arange(void *start, void *end, void *step, dtype type)
{
    switch(type) {
        case uint8:
			return arange_uint8(*(uint8_t *)start, *(uint8_t *)end, *(uint8_t *)step);
        case uint16:
			return arange_uint16(*(uint16_t *)start, *(uint16_t *)end, *(uint16_t *)step);
        case uint32:
			return arange_uint32(*(uint32_t *)start, *(uint32_t *)end, *(uint32_t *)step);
        case uint64:
			return arange_uint64(*(uint64_t *)start, *(int64_t *)end, *(uint64_t *)step);
        case int8:
			return arange_int8(*(int8_t *)start, *(int8_t *)end, *(int8_t *)step);
        case int16:
			return arange_int16(*(int16_t *)start, *(int16_t *)end, *(int16_t *)step);
        case int32:
			return arange_int32(*(int32_t *)start, *(int32_t *)end, *(int32_t *)step);
        case int64:
			return arange_int64(*(int64_t *)start, *(int64_t *)end, *(int64_t *)step);
        case float32:
			return arange_float32(*(float *)start, *(float *)end, *(float *)step);
        case float64:
			return arange_float64(*(double *)start, *(double *)end, *(double *)step);
        default:
			return 0;
    }
}
