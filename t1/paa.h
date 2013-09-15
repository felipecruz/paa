#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#ifndef _PAA_H_
#define _PAA_H_

int knth_nk (int array[], int length, int k);
int knth_merge (int array[], int length, int k);
int knth_n_mom (int array[], int length, int k);
int knth_n_quickselect (int array[], int length, int k);

int *gen_instance_type1 (int length);

void print_array (int array[], int length);
void _mergesort (int *array, int length);
int _knth_merge (int array[], int length, int k);
int randon_range (int a, int b);
int has_n (int *array, int length, int n);

#endif
