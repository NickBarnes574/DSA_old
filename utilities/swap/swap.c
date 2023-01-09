#include "swap.h"

void swap(void *position_1, void *position_2, size_t size)
{
    unsigned char *x = position_1;
    unsigned char *y = position_2;
    unsigned char temp = 0;

    while(size)
    {
        // swap
        temp = *x;
        *x = *y;
        *y = temp;

        // update variables
        *x++;
        *y++;
        temp --;
    }
}