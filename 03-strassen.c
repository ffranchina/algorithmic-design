#include <stdio.h>
#include <stdlib.h>

#include "prettyprint.h"

#define SIZE 4

void add(double *A, double *B, double *C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i * size + j] = A[i * size + j] + B[i * size + j];
}

void sub(double *A, double *B, double *C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i * size + j] = A[i * size + j] - B[i * size + j];
}

void fill_blocks(double *A, int size, double *A_11,
        double *A_12, double *A_21, double *A_22) {
    
    int smaller_size = size / 2;

    for (int i = 0; i < smaller_size; i++)
        for (int j = 0; j < smaller_size; j++) {
            A_11[i * smaller_size + j] = A[i * size + j];
            A_12[i * smaller_size + j] = A[i * size + j + smaller_size];
            A_21[i * smaller_size + j] = A[(i + smaller_size) * size + j];
            A_22[i * smaller_size + j] = A[(i + smaller_size) * size + j + smaller_size];
        }
}

void fill_back(double *A_11, double *A_12, double *A_21,
        double *A_22, int size, double *A) {
    
    int bigger_size = size * 2;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            A[i * bigger_size + j] = A_11[i * size + j];
            A[i * bigger_size + j + size] = A_12[i * size + j];
            A[(i + size) * bigger_size + j] = A_21[i * size + j];
            A[(i + size) * bigger_size + j + size] = A_22[i * size + j];
        }
}

void strassen(double *A, double *B, double *C, int size) {
    if (size == 1)
        C[0] = A[0] * B[0];
        
    else {
        int smaller_size = size / 2;
        
        double *M1 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *M2 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *M3 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *M4 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *M5 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *M6 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *M7 = malloc(sizeof(double) * smaller_size * smaller_size);

        double *A_11 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *A_12 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *A_21 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *A_22 = malloc(sizeof(double) * smaller_size * smaller_size);

        double *B_11 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *B_12 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *B_21 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *B_22 = malloc(sizeof(double) * smaller_size * smaller_size);
        
        double *C_11 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *C_12 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *C_21 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *C_22 = malloc(sizeof(double) * smaller_size * smaller_size);

        double *tmp1 = malloc(sizeof(double) * smaller_size * smaller_size);
        double *tmp2 = malloc(sizeof(double) * smaller_size * smaller_size);

        fill_blocks(A, size, A_11, A_12, A_21, A_22);
        fill_blocks(B, size, B_11, B_12, B_21, B_22);

        add(A_11, A_22, tmp1, smaller_size);
        add(B_11, B_22, tmp2, smaller_size);
        strassen(tmp1, tmp2, M1, smaller_size);

        add(A_21, A_22, tmp1, smaller_size);
        strassen(tmp1, B_11, M2, smaller_size);
        
        sub(B_12, B_22, tmp1, smaller_size);
        strassen(A_11, tmp1, M3, smaller_size);

        sub(B_21, B_11, tmp1, smaller_size);
        strassen(A_22, tmp1, M4, smaller_size);

        add(A_11, A_12, tmp1, smaller_size);
        strassen(tmp1, B_22, M5, smaller_size);

        sub(A_21, A_11, tmp1, smaller_size);
        add(B_11, B_12, tmp2, smaller_size);
        strassen(tmp1, tmp2, M6, smaller_size);

        sub(A_12, A_22, tmp1, smaller_size);
        add(B_21, B_22, tmp2, smaller_size);
        strassen(tmp1, tmp2, M7, smaller_size);

        add(M1, M4, tmp1, smaller_size);
        sub(M7, M5, tmp2, smaller_size);
        add(tmp1, tmp2, C_11, smaller_size);

        add(M3, M5, C_12, smaller_size);

        add(M2, M4, C_21, smaller_size);

        sub(M1, M2, tmp1, smaller_size);
        add(M3, M6, tmp2, smaller_size);
        add(tmp1, tmp2, C_22, smaller_size);

        fill_back(C_11, C_12, C_21, C_22, smaller_size, C);

        free(M1);
        free(M2);
        free(M3);
        free(M4);
        free(M5);
        free(M6);
        free(M7);
        
        free(A_11);
        free(A_12);
        free(A_21);
        free(A_22);

        free(B_11);
        free(B_12);
        free(B_21);
        free(B_22);

        free(C_11);
        free(C_12);
        free(C_21);
        free(C_22);

        free(tmp1);
        free(tmp2);
    }
}

void main() {
    double matA[SIZE * SIZE] = {1,2,3,4, 5,6,7,8, 3,4,5,6, 7,8,9,1};
    double matB[SIZE * SIZE] = {3,4,5,7, 1,2,4,5, 1,8,7,6, 4,3,2,1};
    double matC[SIZE * SIZE];

    printf("Matrix A:");
    print_matrix(matA, SIZE);

    strassen(matA, matB, matC, SIZE);

    printf("Matrix B:");
    print_matrix(matB, SIZE);

    printf("Matrix C:");
    print_matrix(matC, SIZE);
}
