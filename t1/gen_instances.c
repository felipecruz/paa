#include "paa.h"

int *gen_instance_type1 (int length) {
    int *aux = (int*) malloc (sizeof (int) * length);
    int i;
    int n;
    FILE *f;
    char fname[100];

    sprintf (fname, "%d.txt", length);
    f = fopen(fname, "w");
    if (f == NULL)
        exit(-1);

    printf ("Instance size: %d  filename:%s\n", length, fname);
    for (i = 0; i < length;) {
        aux[i] = 0;
        n = randon_range (1, length);
        //printf ("generate number %d\n", n);
        //if (!has_n (aux, i, n)) {
            aux[i] = n;
            fprintf (f, "%d\n", n);
            i++;
        //} 
    }

    fclose (f);
    return aux;
}

#ifdef MAIN
int main (int argc, char **argv) {
    int i;
    int instance_size;
    int *instance;

    for (i = 0; i < 12; i++) {
        srand (time (NULL));
        instance_size = 1000 * pow (2, i);
        instance = gen_instance_type1 (instance_size);
        free (instance);
    }
    
    return 0;
}
#endif
