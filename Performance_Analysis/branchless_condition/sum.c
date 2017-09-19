#include "sum.h"
#include "generic.h"

int sum_array_normal(int * array, size_t size)
{
        unsigned int i;
        int sum = 0;
        for (i = 0; i < size; i++){
                if (array[i] >= 128){
                        sum += array[i];
                }
        }
        return sum;
}

int sum_array_bitwise(int * array, size_t size)
{
        unsigned int i;
        int sum = 0;
        for (i = 0; i < size; i++){
                sum += ~(array[i] - 128) >> 31 & array[i];
        }
        return sum;
}

int sum_array_cmov(int * array, size_t size)
{
        unsigned int i;
        int sum = 0;
        for (i = 0; i < size; i++){
                sum += (array[i] >= 128) ? array[i] : 0;
        }
        return sum;
}
