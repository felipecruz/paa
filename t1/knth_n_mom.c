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
        //printf ("result array[%d] val: %d = %d\n", i, array[i], result[i]);
        if (result[i] == middle)
            return array[i];

    }

    return -1;
}



int knth_n_mom (int array[], int length, int k) {
    int mom, i;
    int i1, i2, i3, i4, i5;
    int sizes[5];
    int left[length/2], right[length/2];
    int left_size, right_size;
    int medians[5] = {0, 0, 0, 0, 0};
    int remainder;

    /* initialize auxiliary arrays sizes */
    for (i = 0; i < 5; i++) {
        sizes[i] = length / 5;
        printf ("Initial slice size %d: %d\n", i, sizes[i]);
    }

    /* handle remainder numbers */
    remainder = length % 5;
    for (i = 0; i < 5; i++) {
        if (remainder > 0 && remainder--)
            sizes[i] += 1;
        printf ("Final size %d: %d\n", i, sizes[i]);
    }

    i1 = 0;
    i2 = sizes[0];
    i3 = i2 + sizes[1];
    i4 = i3 + sizes[2];
    i5 = i4 + sizes[3];

    print_array (&array[i1], sizes[0]);
    print_array (&array[i2], sizes[1]);
    print_array (&array[i3], sizes[2]);
    print_array (&array[i4], sizes[3]);
    print_array (&array[i5], sizes[4]);

    medians[0] = median (&array[i1], sizes[0]);
    medians[1] = median (&array[i2], sizes[1]);
    medians[2] = median (&array[i3], sizes[2]);
    medians[3] = median (&array[i4], sizes[3]);
    medians[4] = median (&array[i5], sizes[4]);

    mom = median (medians, 5);

    printf ("MOM %d\n", mom);
    
    left_size = 0;
    right_size = 0;

    /* partition */
    for (i = 0; i < length; i ++) {
        if (array[i] < mom) {
            left[left_size++] = array[i];
        } else {
            right[right_size++] = array[i];
        }
    }

    print_array (left, left_size);
    print_array (right, right_size);

    exit(0);

    if (k < left_size)
        return knth_n_mom (left, left_size, k);
    else
        return knth_n_mom (right, right_size, length - left_size);
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
