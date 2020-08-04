#include <pthread.h>
#include <stdint.h>
#include "calculate.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

void *pcmax(void *mess)
{
	message *m = (message *)mess;
    size_t index = 0;
    void *data = m->data;
    size_t size = m->size;
	switch(m->type) {
		case uint8:
            data = (uint8_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((uint8_t *)data+index) < (*((uint8_t *)data+i)))
                    index = i;
			break;
		case uint16:
            data = (uint16_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((uint16_t *)data+index) < (*((uint16_t *)data+i)))
                    index = i;
			break;
		case uint32:
            data = (uint32_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((uint32_t *)data+index) < (*((uint32_t *)data+i)))
                    index = i;
			break;
		case uint64:
            data = (uint64_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((uint64_t *)data+index) < (*((uint64_t *)data+i)))
                    index = i;
			break;
		case int8:
            data = (int8_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((int8_t *)data+index) < (*((int8_t *)data+i)))
                    index = i;
			break;
		case int16:
            data = (int16_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((int16_t *)data+index) < (*((int16_t *)data+i)))
                    index = i;
			break;
		case int32:
            data = (int32_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((int32_t *)data+index) < (*((int32_t *)data+i)))
                    index = i;
			break;
		case int64:
            data = (int64_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((int64_t *)data+index) < (*((int64_t *)data+i)))
                    index = i;
			break;
		case float32:
            data = (float *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((float *)data+index) < (*((float *)data+i)))
                    index = i;
			break;
		case float64:
            data = (double *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((double *)data+index) < (*((double *)data+i)))
                    index = i;
			break;
		default:
			break;
	}
	m->index = index + m->bindex;
    return 0;
}

void *pcmin(void *mess)
{
	 message *m = (message *)mess;
    size_t index = 0;
    void *data = m->data;
    size_t size = m->size;
	switch(m->type) {
		case uint8:
            data = (uint8_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((uint8_t *)data+index) > (*((uint8_t *)data+i)))
                    index = i;
			break;
		case uint16:
            data = (uint16_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((uint16_t *)data+index) > (*((uint16_t *)data+i)))
                    index = i;
			break;
		case uint32:
            data = (uint32_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((uint32_t *)data+index) > (*((uint32_t *)data+i)))
                    index = i;
			break;
		case uint64:
            data = (uint64_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((uint64_t *)data+index) > (*((uint64_t *)data+i)))
                    index = i;
			break;
		case int8:
            data = (int8_t *)data  + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((int8_t *)data+index) > (*((int8_t *)data+i)))
                    index = i;
			break;
		case int16:
            data = (int16_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((int16_t *)data+index) > (*((int16_t *)data+i)))
                    index = i;
			break;
		case int32:
            data = (int32_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((int32_t *)data+index) > (*((int32_t *)data+i)))
                    index = i;
			break;
		case int64:
            data = (int64_t *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((int64_t *)data+index) > (*((int64_t *)data+i)))
                    index = i;
			break;
		case float32:
            data = (float *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((float *)data+index) > (*((float *)data+i)))
                    index = i;
			break;
		case float64:
            data = (double *)data + m->bindex;
            for(size_t i=0; i < size; i++)
                if(*((double *)data+index) > (*((double *)data+i)))
                    index = i;
			break;
		default:
			break;
	}
	m->index = index + m->bindex;
    return 0;
}

size_t pmcmax(message *mess, int mess_num)
{
	message *m = (message *)mess;
    size_t index = m->index;
    void *data = m->data;
	switch(m->type) {
		case uint8:
            for(int i=0; i < mess_num; i++)
                if(*((uint8_t *)data + index) < (*((uint8_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case uint16:
            for(int i=0; i < mess_num; i++)
                if(*((uint16_t *)data + index) < (*((uint16_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case uint32:
            for(int i=0; i < mess_num; i++)
                if(*((uint32_t *)data + index) < (*((uint32_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case uint64:
            for(int i=0; i < mess_num; i++)
                if(*((uint64_t *)data + index) < (*((uint64_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case int8:
            for(int i=0; i < mess_num; i++)
                if(*((int8_t *)data + index) < (*((int8_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case int16:
            for(int i=0; i < mess_num; i++)
                if(*((int16_t *)data + index) < (*((int16_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case int32:
            for(int i=0; i < mess_num; i++)
                if(*((int32_t *)data + index) < (*((int32_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case int64:
            for(int i=0; i < mess_num; i++)
                if(*((int64_t *)data + index) < (*((int64_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case float32:
            for(int i=0; i < mess_num; i++)
                if(*((float *)data + index) < (*((float *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case float64:
            for(int i=0; i < mess_num; i++)
                if(*((double *)data + index) < (*((double *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		default:
			break;
	}
    return index;
}


size_t pmcmin(message *mess, int mess_num)
{
	message *m = (message *)mess;
    size_t index = m->index;
    void *data = m->data;
	switch(m->type) {
		case uint8:
            for(int i=0; i < mess_num; i++)
                if(*((uint8_t *)data + index) > (*((uint8_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case uint16:
            for(int i=0; i < mess_num; i++)
                if(*((uint16_t *)data + index) > (*((uint16_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case uint32:
            for(int i=0; i < mess_num; i++)
                if(*((uint32_t *)data + index) > (*((uint32_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case uint64:
            for(int i=0; i < mess_num; i++)
                if(*((uint64_t *)data + index) > (*((uint64_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case int8:
            for(int i=0; i < mess_num; i++)
                if(*((int8_t *)data + index) > (*((int8_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case int16:
            for(int i=0; i < mess_num; i++)
                if(*((int16_t *)data + index) > (*((int16_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case int32:
            for(int i=0; i < mess_num; i++)
                if(*((int32_t *)data + index) > (*((int32_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case int64:
            for(int i=0; i < mess_num; i++)
                if(*((int64_t *)data + index) > (*((int64_t *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case float32:
            for(int i=0; i < mess_num; i++)
                if(*((float *)data + index) > (*((float *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		case float64:
            for(int i=0; i < mess_num; i++)
                if(*((double *)data + index) > (*((double *)data + (m+i)->index)))
                    index = (m+i)->index;
			break;
		default:
			break;
	}
    return index;
}

size_t amaxmin_no_thread(array *arr, int max_min) 
{
	message m;
	m.bindex = 0;
	m.data = arr->data;
	m.size = arr->size;
	m.type = arr->type;
	max_min ? pcmax(&m) : pcmin(&m);
	return m.index;
}

message *_init_mess(array *arr,int thread_num) {
    message *m = calloc(thread_num, sizeof(message));  
	if(!m) return m;
    size_t avg_size = arr->size / thread_num;
    size_t bindex = 0;
    for(int i=0; i < thread_num - 1; i++) {
       (m + i)->data = arr->data;
       (m + i)->size = avg_size;
       (m + i)->bindex = bindex;
       (m + i)->type = arr->type;
       bindex += avg_size;
    }
    (m + (thread_num - 1))->data = arr->data;
    (m + (thread_num - 1))->bindex = bindex;
    (m + (thread_num - 1))->size = arr->size - bindex;
    (m + (thread_num - 1))->type = arr->type;
	return m;
}

size_t amaxmin_thread(array *arr, int max_min)
{
    int thread_num = sysconf(_SC_NPROCESSORS_CONF);
	printf("@%d\n", thread_num);
    size_t res = -1;
    pthread_t *t = calloc(thread_num, sizeof(pthread_t));  
    if(!t) return -1;
	message *m = _init_mess(arr, thread_num);
    if(!m) { free(t); return -1; }
    for(int i=0; i < thread_num; i++) 
		max_min ? pthread_create(t+i, NULL, pcmax, m+i) : pthread_create(t+i, NULL, pcmin, m+i);
    for(int i=0; i < thread_num; i++) 
        pthread_join(*(t+i), NULL);
    res = max_min ? pmcmax(m, thread_num) : pmcmin(m, thread_num);
    free(t);
    free(m);
    return res;
}

size_t amaxmin(array *arr, int max_min)
{
	return arr->size > USE_MULTHREAD_SIZE ? amaxmin_thread(arr, max_min) : amaxmin_no_thread(arr, max_min);
}

size_t amax(array *arr) 
{
    return amaxmin(arr, 1);
}

size_t amin(array *arr) 
{
    return amaxmin(arr, 0);
}

