#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

#include "paa.h"

int _knth_n_quickselect (int array[], int length, int k) {
    int i;
    int c = 0;
    int pivot;
    int left_size;

    c = randon_range (0, length - 1);
    pivot = array[c];

    /* coloca o pivot no final para nao passarmos por ele no loop
     * de particionamento */
    swap (array, c, length - 1);

    left_size = 0;

    for (i = 0; i < length - 1; i++) {
        if (array[i] < pivot) {
            swap (array, i, left_size++);
        }
    }

    /* coloca pivot de volta logo depois do lado esquerdo */
    swap (array, left_size, length -1);

    if (k == left_size)
        return pivot;

    if (k < left_size) {
        return _knth_n_quickselect (array, left_size, k);
    } else {
        return _knth_n_quickselect (&array[left_size + 1],
                                    length - left_size - 1,
                                    k - left_size - 1);
    }
}

int knth_n_quickselect (int array[], int length, int k) {
    return _knth_n_quickselect (array, length, k - 1);
}

#ifdef MAIN
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
#endif
