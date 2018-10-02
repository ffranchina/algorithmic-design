#include <stdio.h>

#include "prettyprint.h"

#define LEN 10

#define SX(X) ((X) * 2 + 1)
#define DX(X) ((X) * 2 + 2)
#define UP(X) (((X) - 1) / 2)

void heapify(double *a, int len, int elem) {
    int max, sx, dx, tmp;

    max = elem;
    sx = SX(elem);
    dx = DX(elem);

    if (sx < len && a[sx] > a[max])
        max = sx;

    if (dx < len && a[dx] > a[max])
        max = dx;

    if (max != elem) {
        tmp = a[elem];
        a[elem] = a[max];
        a[max] = tmp;

        heapify(a, len, max);
    }
}

void heapsort(double *a, int len) {
    double tmp;

    for (int i = len / 2 - 1; i >= 0; i--)
        heapify(a, len, i);

    for (int i = len - 1; i > 0; i--) {
        tmp = a[i];
        a[i] = a[0];
        a[0] = tmp;

        heapify(a, i, 0);
    }
}

void main() {
    double array[LEN] = {4, 6, 2, 6, 1, 8, 9, 3, 0, 7};

    printf("Original array:\n");
    print_array(array, LEN);

    heapsort(array, LEN);

    printf("Sorted array:\n");
    print_array(array, LEN);
}
