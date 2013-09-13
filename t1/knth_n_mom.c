#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "paa.h"

/* if K < 5, use knth_merge */
int knth_merge (int array[], int length, int k) {
    int copy_array[length];

    memcpy (copy_array, array, length * sizeof (int));

    _mergesort (copy_array, length);

    return copy_array[k - 1];
}
/* end of copy paste knth_merge */

int median (int array[], int length) {
    int i, j;
    int middle = length / 2;
    int result[length];

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

    return -1;
}



int knth_n_mom (int array[], int length, int k) {
    int c = 0;
    int mom, i, j;
    int remainder = length % 5;
    int group_number = (length / 5);
    int sizes[group_number];
    int groups[group_number][5];
    int medians[group_number + 1];
    int left[length/2], right[length/2];
    int left_size, right_size;

    /* sort and merge for small arrays */
    if  (length <= 5)
        return knth_merge (array, length, k);

    /* If X % 5 > 0 then we need one more group
     * 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
     * |      1     |       2       |  3        |
     */
    if (remainder > 0)
        group_number++;

    /* initialize auxiliary arrays sizes */
    for (i = 0; i < group_number; i++) {
        sizes[i] = 5;
    }

     /* The size of the last group is the remainder itself */
    if (remainder > 0)
        sizes[group_number - 1] = remainder;

#ifdef DEBUG
    for (i = 0; i < group_number; i++) {
        printf("Size group:%d is %d\n", i, sizes[i]);
    }
#endif

    for (i = 0; i < group_number; i++) {
        for (j = 0; j < 5; j++) {
#ifdef DEBUG
            printf ("Element %d group:%d sizes:%d %d\n", array[c], i,
                                                         sizes[i], length);
#endif
            groups[i][j] = array[c];
            c++;
            if (c >= length) {
                break;
            }
        }
    }

#ifdef DEBUG
    for (i = 0; i < group_number; i++) {
        print_array (groups[i], sizes[i]);
    }
#endif

    for (i = 0; i < group_number; i++) {
        medians[i] = 0; /* dummy init */
        medians[i] = median (groups[i], sizes[i]);
    }

#ifdef DEBUG
    for (i = 0; i < group_number; i++) {
        printf ("Median group:%d is %d\n", i, medians[i]);
    }
#endif

    mom = median (medians, group_number);

#ifdef DEBUG
    printf ("MOM %d\n", mom);
#endif


    left_size = 0;
    right_size = 0;

    /* partition */
    for (i = 0; i < length; i ++) {
        if (array[i] < mom) {
            left[left_size++] = array[i];
        } else if (array[i] > mom){
            right[right_size++] = array[i];
        }
    }

#ifdef DEBUG
    print_array (left, left_size);
    print_array (right, right_size);
    printf ("ls: %d rs:%d k:%d\n", left_size, right_size, k);
#endif

    if (k == left_size + 1)
        return mom;

    if (k < left_size + 1) {
        return knth_n_mom (left, left_size, k);
    } else {
        return knth_n_mom (right, right_size, k - left_size - 1);
    }
}

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
