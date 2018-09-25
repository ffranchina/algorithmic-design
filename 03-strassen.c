#include <stdio.h>

#include "prettyprint.h"

#define SIZE 4

void main() {
    double matA[SIZE * SIZE] = {1,2,3,4, 5,6,7,8, 3,4,5,6, 7,8,9,1};
    double matB[SIZE * SIZE] = {3,4,5,7, 1,2,4,5, 1,8,7,6, 4,3,2,1};

    printf("Matrix A:");
    print_matrix(matA, SIZE);

    printf("Matrix B:");
    print_matrix(matB, SIZE);
}
