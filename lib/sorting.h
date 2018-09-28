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
