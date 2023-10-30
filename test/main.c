#include "test.h"

test *Cat;

int main()
{
    Cat = (test *) malloc(2 * sizeof(test));
    change(2, 2);
    for (int i = 0; i < 2; i++)
    {
        printf("%d\n", Cat[i].a);
    }
}