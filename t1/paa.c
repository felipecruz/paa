#include "paa.h"

void print_array (int array[], int length) {
    int i;

    for (i = 0; i < length; i++) {
        printf ("%d ", array[i]);
    }

    printf ("\n");
}

int randon_range (int min, int max)
{
    int r = min + (rand() % (int)(max - min + 1));
    return r;
}

int *init_zeros_array (int length) {
    int i;
    int *array;

    assert (length > 0);

    array = malloc (sizeof (int) * length);

    for (i = 0; i < length; i++) {
        array[i] = 0;
    }

    return array;
}

int check_marked (int *array, int num) {
    return 0 == array[num];
}

void mark_int (int *array, int num, int val) {
    array[num] = val;
}

void _mergesort (int *array, int length) {
    int c, i, j;
    int *left, *right;
    int middle = length / 2;

    if (length == 1 || length == 0) {
        return;
    }

    i = 0;
    c = 0;
    j = middle;

    left = malloc (sizeof (int) * middle);
    right = malloc (sizeof (int) * (length - middle));

    memcpy (left, array, middle);
    memcpy (right, &array[middle], length - middle);

    _mergesort (left, middle);
    _mergesort (right, length - middle);

    while (c < length) {
        if (array[i] < array[j] && i < middle) {
            array[c] = array[i++];
        } else if (array[i] > array[j] && j < length) {
            array[c] = array[j++];
        } else if (i >= middle) {
            array[c] = array[j++];
        } else if (j >= length) {
            array[c] = array[i++];
        }
        c++;
    }

    free (left);
    free (right);
}

/* if K < 5, use knth_merge */
int _knth_merge (int array[], int length, int k) {
    int copy_array[length];

    memcpy (copy_array, array, length * sizeof (int));

    _mergesort (copy_array, length);

    return copy_array[k - 1];
}
/* end of copy paste knth_merge */
