#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "generator.h"

#define ATERMINATOR -1

void *kmp_prefix(char *pattern, int *prefix_output) {
    int pos = 0;

    prefix_output[0] = 0;

    for (int i = 1; i < strlen(pattern); i++) {
        int j = prefix_output[i - 1];

        while (j > 0 && pattern[i] != pattern[j])
            j = prefix_output[j - 1];

        if (pattern[i] == pattern[j]) j++;

        prefix_output[i] = j;
    }
}

int *occurrences_kmp(char *text, char *pattern) {
    int t_cursor = 0, p_cursor = 0;
    int prefix[strlen(pattern)];
    int *positions, counter = 0;
    NodeList *list = NULL;

    kmp_prefix(pattern, prefix);
    
    while (t_cursor < strlen(text)) {
        if (text[t_cursor] == pattern[p_cursor]) {
            t_cursor++;
            p_cursor++;
        }

        if (p_cursor == strlen(pattern)) {
            push(&list, t_cursor - p_cursor);
            counter++;
            p_cursor = prefix[p_cursor - 1];
        } else if (t_cursor < strlen(text) && pattern[p_cursor] != text[t_cursor]) {
            if (p_cursor != 0) p_cursor = prefix[p_cursor - 1];
            else t_cursor++;
        }
    }

    push(&list, ATERMINATOR);
    counter++;

    positions = malloc(sizeof(int) * (counter));
    for (int i = counter - 1; i >= 0; i--)
        positions[i] = pop(&list);

    return positions;
}

void main() {
    char *string = generate_dna_string(1000);
    char pattern[] = "TACT";
    int *positions, counter = 0;

    printf("%s\n", string);

    printf("\nLooking for the pattern [%s]", pattern);
    positions = occurrences_kmp(string, pattern);

    printf("\nOccurrencies found: (");
    while (positions[counter] != ATERMINATOR)
        printf(" %d", positions[counter++]);
    printf(" )\n");

    free(positions);
    free(string);
}
