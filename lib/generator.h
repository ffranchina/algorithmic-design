#include <stdlib.h>

char *generate_dna_string(int len) {
    char *string = malloc(sizeof(char) * len + 1);
    char comp[4] = {'A', 'C', 'T', 'G'};

    for (int i = 0; i < len; i++)
        string[i] = comp[rand() % 4];
    
    string[len] = '\0';

    return string;
}
