#include "paa.h"

int knth_merge (int array[], int length, int k) {
    int kn = 0;
    int *copy_array = (int*) malloc (sizeof (int) * length);

    /* não alteramos o array original por isso fazemos uma cópia */
    memcpy (copy_array, array, length * sizeof (int));

    _mergesort (copy_array, length);

    kn = copy_array[k - 1];
    free (copy_array);

    return kn;
}

#ifdef MAIN
int main (int argc, char **argv)
{
    int array[] = {99, 3, 70, 8, -1, -300, 4, 120, 340, 1000, 2, 1, -500};
    int numbers[11] = {8, 7, 1, 2, 4, 5, 3, 9, 11, -200, 12};

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
#endif
