#include "average_filter.h"

void reset_buffer(average_filter *filter)
{
    filter->sum = 0;
    filter->out = 0;
    filter->count = 0;
    
    for (int i = 0; i < AVERAGE_LENGTH; i++)
    {
        filter->buffer[i] = 0;
    }
    return;
}

void apply_filter(average_filter *filter, int16_t input, int16_t *output)
{
    filter->sum += (input - filter->buffer[filter->count]);
    filter->buffer[filter->count] = input;
    filter->count++;
    if (filter->count == AVERAGE_LENGTH)
    {
        filter->count = 0;
    }
    filter->out = filter->sum / AVERAGE_LENGTH;

    *output = filter->out;
}