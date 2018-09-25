#include <stdio.h>

#include "prettyprint.h"

#define LEN 10

void inssort(double *a, int dimension) {
    double tmp;

    for (int i = 1; i < dimension; i++)
        for (int j = i; j > 0; j--)
            if (a[j] < a[j - 1]) {
                tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;
            }
}

int main() {
    double array[LEN] = {2, 5, 1, 3, 6, 9, 0, 5, 7, 4};

    printf("Original array:\n");
    print_array(array, LEN);

    inssort(array, LEN);

    printf("Sorted array:\n");
    print_array(array, LEN);
}
