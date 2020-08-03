#include <pthread.h>
#include <stdint.h>
#include "calculate.h"

int64_t max_int64(void *data, size_t size)
{
    int64_t max = *((int64_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((int64_t *)data+i) > max) max = (*((int64_t *)data+i));
	return max;
}

int32_t max_int32(void *data, size_t size)
{
    int32_t max = *((int32_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((int32_t *)data+i) > max) max = (*((int32_t *)data+i));
	return max;
}

int16_t max_int16(void *data, size_t size)
{
    int16_t max = *((int16_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((int16_t *)data+i) > max) max = (*((int16_t *)data+i));
	return max;
}

int8_t max_int8(void *data, size_t size)
{
    int8_t max = *((int8_t *)data);
	for(size_t i=0; i < size; i++) 
		if(*((int8_t *)data+i) > max) max = (*((int8_t *)data+i));
	return max;
}


uint64_t max_uint64(void *data, size_t size)
{
    uint64_t max = *((uint64_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((uint64_t *)data+i) > max) max = (*((uint64_t *)data+i));
	return max;
}

uint32_t max_uint32(void *data, size_t size)
{
    uint32_t max = *((uint32_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((uint32_t *)data+i) > max) max = (*((uint32_t *)data+i));
	return max;
}

uint16_t max_uint16(void *data, size_t size)
{
    uint16_t max = *((uint16_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((uint16_t *)data+i) > max) max = (*((uint16_t *)data+i));
	return max;
}

uint8_t max_uint8(void *data, size_t size)
{
    uint8_t max = *((uint8_t *)data);
	for(size_t i=0; i < size; i++) 
		if(*((uint8_t *)data+i) > max) max = (*((uint8_t *)data+i));
	return max;
}

float max_float32(void *data, size_t size)
{
    float max = *((float *)data);
	for(size_t i=0; i < size; i++) 
		if(*((float *)data+i) > max) max = (*((float *)data+i));
	return max;
}

double max_float64(void *data, size_t size)
{
    double max = *((double *)data);
	for(size_t i=0; i < size; i++) 
		if(*((double *)data+i) > max) max = (*((double *)data+i));
	return max;
}


int64_t min_int64(void *data, size_t size)
{
    int64_t min = *((int64_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((int64_t *)data+i) < min) min = (*((int64_t *)data+i));
	return min;
}

int32_t min_int32(void *data, size_t size)
{
    int32_t min = *((int32_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((int32_t *)data+i) < min) min = (*((int32_t *)data+i));
	return min;
}

int16_t min_int16(void *data, size_t size)
{
    int16_t min = *((int16_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((int16_t *)data+i) < min) min = (*((int16_t *)data+i));
	return min;
}

int8_t min_int8(void *data, size_t size)
{
    int8_t min = *((int8_t *)data);
	for(size_t i=0; i < size; i++) 
		if(*((int8_t *)data+i) < min) min = (*((int8_t *)data+i));
	return min;
}


uint64_t min_uint64(void *data, size_t size)
{
    uint64_t min = *((uint64_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((uint64_t *)data+i) < min) min = (*((uint64_t *)data+i));
	return min;
}

uint32_t min_uint32(void *data, size_t size)
{
    uint32_t min = *((uint32_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((uint32_t *)data+i) < min) min = (*((uint32_t *)data+i));
	return min;
}

uint16_t min_uint16(void *data, size_t size)
{
    uint16_t min = *((uint16_t *)data);
	for(size_t i=0; i < size; i++)
		if(*((uint16_t *)data+i) < min) min = (*((uint16_t *)data+i));
	return min;
}

uint8_t min_uint8(void *data, size_t size)
{
    uint8_t min = *((uint8_t *)data);
	for(size_t i=0; i < size; i++) 
		if(*((uint8_t *)data+i) < min) min = (*((uint8_t *)data+i));
	return min;
}

float min_float32(void *data, size_t size)
{
    float min = *((float *)data);
	for(size_t i=0; i < size; i++) 
		if(*((float *)data+i) < min) min = (*((float *)data+i));
	return min;
}

double min_float64(void *data, size_t size)
{
    double min = *((double *)data);
	for(size_t i=0; i < size; i++) 
		if(*((double *)data+i) < min) min = (*((double *)data+i));
	return min;
}

void pcmax(void *mess)
{
	struct message *m = (struct message *)mess;
	switch(m->type) {
		case uint8:
			*(uint8_t *)m->value = max_uint8(m->data, m->size);
			break;
		case uint16:
			*(uint16_t *)m->value = max_uint16(m->data, m->size);
			break;
		case uint32:
			*(uint32_t *)m->value = max_uint32(m->data, m->size);
			break;
		case uint64:
			*(uint64_t *)m->value = max_uint64(m->data, m->size);
			break;
		case int8:
			*(int8_t *)m->value = max_int8(m->data, m->size);
			break;
		case int16:
			*(int16_t *)m->value = max_int16(m->data, m->size);
			break;
		case int32:
			*(int32_t *)m->value = max_int32(m->data, m->size);
			break;
		case int64:
			*(int64_t *)m->value = max_int64(m->data, m->size);
			break;
		case float32:
			*(float *)m->value = max_float32(m->data, m->size);
			break;
		case float64:
			*(double *)m->value = max_float64(m->data, m->size);
			break;
		default:
			break;
	}
}

void pcmim(void *mess)
{
	struct message *m = (struct message *)mess;
	switch(m->type) {
		case uint8:
			*(uint8_t *)m->value = min_uint8(m->data, m->size);
			break;
		case uint16:
			*(uint16_t *)m->value = min_uint16(m->data, m->size);
			break;
		case uint32:
			*(uint32_t *)m->value = min_uint32(m->data, m->size);
			break;
		case uint64:
			*(uint64_t *)m->value = min_uint64(m->data, m->size);
			break;
		case int8:
			*(int8_t *)m->value = min_int8(m->data, m->size);
			break;
		case int16:
			*(int16_t *)m->value = min_int16(m->data, m->size);
			break;
		case int32:
			*(int32_t *)m->value = min_int32(m->data, m->size);
			break;
		case int64:
			*(int64_t *)m->value = min_int64(m->data, m->size);
			break;
		case float32:
			*(float *)m->value = min_float32(m->data, m->size);
			break;
		case float64:
			*(double *)m->value = min_float64(m->data, m->size);
			break;
		default:
			break;
	}
}
