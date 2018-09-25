#include <stdio.h>

void print_array(double *buffer, int len) {
    printf("[ ");    
    for (int i = 0; i < len; i++)
        printf("%2.2f ", buffer[i]);
    printf("]\n");
}
