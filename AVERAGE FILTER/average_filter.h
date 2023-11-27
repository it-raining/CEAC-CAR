#ifndef _AVERAGE_FILTER_H_
#define _AVERAGE_FILTER_H_

// #include "main.h"
#define AVERAGE_LENGTH 10
#define map(a, b, c, d, e) (((a - b)*1.0/(c - b)) * (e - d) + d)

typedef struct
{
    int16_t buffer[AVERAGE_LENGTH];
    int32_t sum;
    int16_t out;
    uint16_t count; 
} average_filter;

void reset_buffer(average_filter *filter);
void apply_filter(average_filter *filter, int16_t input);

#endif
