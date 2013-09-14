#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

#include "paa.h"

int knth_merge (int array[], int length, int k) {
    int copy_array[length];

    memcpy (copy_array, array, length * sizeof (int));

    _mergesort (copy_array, length);

    return copy_array[k - 1];
}

int randon_range (int a, int b)
{
    int r = a + rand() / (RAND_MAX / (b - 1 - a + 1) + 1);
    return r;
}

int knth_n_quickselect (int array[], int length, int k) {
    int pivot;
    int c = 0;
    int i, j;
    int left[length/2], right[length/2];
    int left_size, right_size;

    /* sort and merge for small arrays */
    if  (length <= 5)
        return knth_merge (array, length, k);

    c = randon_range (0, length);
    pivot = array[c];

#ifdef DEBUG
    printf ("Pivot %d\n", pivot);
#endif

    left_size = 0;
    right_size = 0;

    /* partition */
    for (i = 0; i < length; i ++) {
        if (array[i] < pivot) {
            left[left_size++] = array[i];
        } else if (array[i] > pivot){
            right[right_size++] = array[i];
        }
    }

#ifdef DEBUG
    print_array (left, left_size);
    print_array (right, right_size);
    printf ("ls: %d rs:%d k:%d\n", left_size, right_size, k);
#endif

    if (k == left_size + 1)
        return pivot;

    if (k < left_size + 1) {
        return knth_n_quickselect (left, left_size, k);
    } else {
        return knth_n_quickselect (right, right_size, k - left_size - 1);
    }
}

int main (int argc, char **argv)
{
    int array[13] = {99, 3, 70, 8, -1, -300, 4, 120, 340, 1000, 2, 1, -500};
    int numbers[11] = {8, 7, 1, 2, 4, 5, 3, 9, 11, -200, 12};

    srand (time (NULL));

    assert (1 == knth_n_quickselect (array, 13, 4));

    assert (-200 == knth_n_quickselect (numbers, 11, 1));
    assert (1 == knth_n_quickselect (numbers, 11, 2));
    assert (2 == knth_n_quickselect (numbers, 11, 3));
    assert (3 == knth_n_quickselect (numbers, 11, 4));
    assert (4 == knth_n_quickselect (numbers, 11, 5));
    assert (5 == knth_n_quickselect (numbers, 11, 6));
    assert (7 == knth_n_quickselect (numbers, 11, 7));
    assert (8 == knth_n_quickselect (numbers, 11, 8));
    assert (9 == knth_n_quickselect (numbers, 11, 9));
    assert (11 == knth_n_quickselect (numbers, 11, 10));
    assert (12 == knth_n_quickselect (numbers, 11, 11));

    return 0;
}
