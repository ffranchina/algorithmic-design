#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "prettyprint.h"
#include "sorting.h"

#define LEN 10
#define BLOCK_SIZE 5

double quickselect(double *, int, int, int, int);

int select_pivot(double *a, int len, int lpos, int rpos) {
    int n_blocks = ceil((rpos - lpos) / BLOCK_SIZE);
    int chunk_len, pos;

    double *medians = malloc(sizeof(double) * n_blocks);

    for (int i = 0; i < n_blocks; i++) {
        chunk_len = ((i + 1) * BLOCK_SIZE) <= rpos ? BLOCK_SIZE : rpos % 5;
        inssort(a + (i * BLOCK_SIZE), chunk_len);

        medians[i] = a[i * BLOCK_SIZE + chunk_len / 2];
    }

    pos = (int) quickselect(medians, n_blocks, 0, n_blocks - 1, n_blocks / 2);

    free(medians);

    return n_blocks;
}

void swap(double *a, double *b) {
    double tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(double *a, int len, int lpos, int rpos, int pivot) {
    double value = a[pivot];
    int index = lpos;

    swap(&a[pivot], &a[rpos]);

    for (int i = lpos; i < rpos; i++)
        if (a[i] < value) {
            swap(&a[index], &a[i]);
            index++;
        }

    swap(&a[rpos], &a[index]);

    return index;
}

double quickselect(double *a, int len, int lpos, int rpos, int k) {
    int pivot;

    if (lpos == rpos)
        return a[lpos];

    pivot = lpos + rand() % (rpos - lpos + 1);
    //pivot = select_pivot(a, len, lpos, rpos);
    pivot = partition(a, len, lpos, rpos, pivot);

    if (k == pivot)
        return a[k];
    else if (k < pivot)
        return quickselect(a, len, lpos, pivot - 1, k);
    else
        return quickselect(a, len, pivot + 1, rpos, k);
}

void main() {
    double array[LEN] = {2, 7, 9, 1, 8, 3, 0, 5, 7, 4};
    double nth;

    printf("Array:\n");
    print_array(array, LEN);

    for (int i = 0; i < LEN; i++) {
        nth = quickselect(array, LEN, 0, LEN - 1, i);
        printf("%dth element of the array: %f\n", i + 1, nth);
    }
}
