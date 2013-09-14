#include "paa.h"

void print_array (int array[], int length) {
    int i;

    for (i = 0; i < length; i++) {
        printf ("%d ", array[i]);
    }

    printf ("\n");
}

void _mergesort (int *array, int length) {
    int copy_array[length];
    int middle = length / 2;
    int c, i, j;

    c = i = 0;
    j = middle;

    if (length == 1) {
        return;
    }

    _mergesort (array, middle);
    _mergesort (&array[middle], length - middle);

    while (c < length) {
        if (array[i] < array[j] && i < middle) {
            copy_array[c] = array[i++];
        } else if (array [i] > array[j] && j < length) {
            copy_array[c] = array[j++];
        } else if (i >= middle) {
            copy_array[c] = array[j++];
        } else if (j >= length) {
            copy_array[c] = array[i++];
        }
        c++;
    }

    memcpy (array, copy_array, length * sizeof (int));
}

/* if K < 5, use knth_merge */
int _knth_merge (int array[], int length, int k) {
    int copy_array[length];

    memcpy (copy_array, array, length * sizeof (int));

    _mergesort (copy_array, length);

    return copy_array[k - 1];
}
/* end of copy paste knth_merge */
