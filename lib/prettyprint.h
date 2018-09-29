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

void print_adjm(short *buffer, int size) {
    printf("\n  ");
    for (int i = 0; i < size; i++) printf("_%2d", i);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%2d|", i);

        for(int j = 0; j < size; j++)
            if (j < size - 1)
                printf("%2d ", buffer[i * size + j]);
            else
                printf("%2d\n", buffer[i * size + j]);
    }
}
