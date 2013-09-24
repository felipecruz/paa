#include "paa.h"

int median (int array[], int length) {
    int i, j;
    int middle = length / 2;
    int result[length];

    if (length == 0)
        return array[0];

    for (i = 0; i < length; i ++) {
        result[i] = 0;
        for (j = 0; j < length; j++) {
            if (array[i] < array[j])
                result[i]++;
        }
    }

    for (i = 0; i < length; i++) {
        if (result[i] == middle)
            return array[i];
    }

    return array[0];
}

int _knth_n_mom (int array[], int length, int k) {
    int c = 0;
    int mom, i;
    int group_number = (length / 5);
    int left_size;
    int *medians = malloc (sizeof (int) * (group_number));

    /* se o array é pequeno usamos knth_nk */
    if (length <= 5)
        return _knth_nk (array, length, k + 1);

    for (i = 0; i < group_number; i++)
        medians[i] = median (&array[i*5], 5);

    mom = _knth_n_mom (medians, group_number, group_number / 2);
    free (medians);

    /* precisamos achar o indice do pivot */
    for (i = 0; i < length; i++){
        if (array[i] == mom) {
            c = i;
            break;
        }
    }

    /* coloca o pivot no final para nao passarmos por ele no loop
     * de particionamento */
    swap (array, c, length - 1);

    left_size = 0;

    for (i = 0; i < length - 1; i++) {
        if (array[i] < mom) {
            swap (array, i, left_size++);
        }
    }

    /* coloca pivot de volta logo depois do lado esquerdo */
    swap (array, left_size, length -1);

    if (k == left_size)
        return mom;

    if (k < left_size) {
        return _knth_n_mom (array, left_size, k);
    } else {
        return _knth_n_mom (&array[left_size + 1],
                            length - left_size - 1,
                            k - left_size - 1);
    }
}

int knth_n_mom (int array[], int length, int k) {
    return _knth_n_mom (array, length, k - 1);
}

#ifdef MAIN
int main (int argc, char **argv)
{
    int array[13] = {99, 3, 70, 8, -1, -300, 4, 120, 340, 1000, 2, 1, -500};
    int numbers[11] = {8, 7, 1, 2, 4, 5, 3, 9, 11, -200, 12};

    int median2[5] = {3, 2, 1, 4, 5};
    int median3[5] = {1, 3, 2, 4, 5};
    int median1[5] = {1, 2, 3, 4, 5};
    int median4[5] = {1, 2, 4, 3, 5};
    int median5[5] = {1, 2, 5, 4, 3};

    printf ("median %d\n", median (median1, 5));
    assert (3 == median (median1, 5));
    assert (3 == median (median2, 5));
    assert (3 == median (median3, 5));
    assert (3 == median (median4, 5));
    assert (3 == median (median5, 5));

    assert (1 == knth_n_mom (median1, 5, 1));
    assert (2 == knth_n_mom (median2, 5, 2));
    assert (3 == knth_n_mom (median3, 5, 3));
    assert (4 == knth_n_mom (median4, 5, 4));
    assert (5 == knth_n_mom (median5, 5, 5));

    assert (1 == knth_n_mom (array, 13, 4));

    assert (-200 == knth_n_mom (numbers, 11, 1));
    assert (1 == knth_n_mom (numbers, 11, 2));
    assert (2 == knth_n_mom (numbers, 11, 3));
    assert (3 == knth_n_mom (numbers, 11, 4));
    assert (4 == knth_n_mom (numbers, 11, 5));
    assert (5 == knth_n_mom (numbers, 11, 6));
    assert (7 == knth_n_mom (numbers, 11, 7));
    assert (8 == knth_n_mom (numbers, 11, 8));
    assert (9 == knth_n_mom (numbers, 11, 9));
    assert (11 == knth_n_mom (numbers, 11, 10));
    assert (12 == knth_n_mom (numbers, 11, 11));

    return 0;
}
#endif
