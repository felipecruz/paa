#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

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


int knth_merge (int array[], int length, int k) {
    int copy_array[length];

    memcpy (copy_array, array, length * sizeof (int));

    _mergesort (copy_array, length);

    return copy_array[k - 1];
}

int main (int argc, char **argv)
{
    int array[] = {99, 3, 70, 8, -1, -300, 4, 120, 340, 1000, 2, 1, -500};
    int numbers[11] = {8, 7, 1, 2, 4, 5, 3, 9, 11, -200, 12};

    print_array (array, 13);
    _mergesort (array, 13);
    print_array (array, 13);

    assert (1 == knth_merge (array, 13, 4));

    assert (-200 == knth_merge (numbers, 11, 1));
    assert (1 == knth_merge (numbers, 11, 2));
    assert (2 == knth_merge (numbers, 11, 3));
    assert (3 == knth_merge (numbers, 11, 4));
    assert (4 == knth_merge (numbers, 11, 5));
    assert (5 == knth_merge (numbers, 11, 6));
    assert (7 == knth_merge (numbers, 11, 7));
    assert (8 == knth_merge (numbers, 11, 8));
    assert (9 == knth_merge (numbers, 11, 9));
    assert (11 == knth_merge (numbers, 11, 10));
    assert (12 == knth_merge (numbers, 11, 11));

    return 0;
}
