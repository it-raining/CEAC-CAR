#ifndef _TEST_H_
#define _TEST_H_
#include<stdio.h>
#include <stdlib.h>
typedef struct
{
    int a;
} test;

extern test *Cat;

void change(int num, int value);

#endif