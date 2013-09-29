#include "paa.h"

int knth_nk (int *array, int length, int k) {
    int i, j;
    int number, curr_min_index;
    int min = INT_MAX;
    int *aux;

    aux = init_zeros_array (length + 1);

    curr_min_index = -1;

    for (i = 0; i < k; i++) {
        min = INT_MAX;
        for (j = 0; j < length; j++) {
            number = array[j];
            if (check_marked (aux, j) && number < min) {
                min = number;
                curr_min_index = j;
            }
        }
        mark_int (aux, curr_min_index, min);
    }

    free (aux);
    return min;
}

#ifdef MAIN
int main (int argc, char **argv)
{
    int numbers[11] = {8, 7, 1, 2, 4, 5, 3, 9, 11, -200, 12};

    assert (-200 == knth_nk (numbers, 11, 1));
    assert (1 == knth_nk (numbers, 11, 2));
    assert (2 == knth_nk (numbers, 11, 3));
    assert (3 == knth_nk (numbers, 11, 4));
    assert (4 == knth_nk (numbers, 11, 5));
    assert (5 == knth_nk (numbers, 11, 6));
    assert (7 == knth_nk (numbers, 11, 7));
    assert (8 == knth_nk (numbers, 11, 8));
    assert (9 == knth_nk (numbers, 11, 9));
    assert (11 == knth_nk (numbers, 11, 10));
    assert (12 == knth_nk (numbers, 11, 11));

    return 0;
}
#endif
