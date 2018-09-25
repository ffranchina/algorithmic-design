#include <stdio.h>

void print_array(double *buffer, int len) {
    printf("[ ");    
    for (int i = 0; i < len; i++)
        printf("%2.2f ", buffer[i]);
    printf("]\n");
}

void print_matrix(double *buffer, int size) {
    printf("\n");
    for (int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if (j < size - 1)
                printf("%2.2f ", buffer[i * size + j]);
            else
                printf("%2.2f\n", buffer[i * size + j]);
}
