#include <time.h>
#include <sys/time.h>

#define START(s) current_utc_time (&s)
#define FINISH(e, s)                                                        \
    current_utc_time (&e);                                                  \
    elapsed = timespecDiff (&e, &s);                                        \
    printf ("SIZE:%d %dnth is %d -- Took %ld msec\n",                       \
            instance_size, k, number, elapsed);                             \


#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include "paa.h"

void current_utc_time(struct timespec *ts) {
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, ts);
#endif
}

int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
           ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

int *get_data (const char *file, int size)
{
    int i = 0;
    int number = 0;
    int *data = malloc (sizeof (int) * size);
    FILE *f = fopen (file, "r");

    if (!f) {
        printf("ERRO");
        exit(-1);
    }

    while (fscanf (f, "%d\n", &number) != EOF) {
        data[i++] = number;
        number = 0;
    }

    fclose(f);

    return data;
}


int main (int argc, char **argv)
{
    int i, f, instance_size, instance_swaps;
    int *instance, *original;
    int k;
    int number;
    char fname[20];
    long elapsed;
    struct timespec s, e;

    char *functions[]= {"kntk_nk", "knth_merge", "knth_n_mom",
                        "knth_n_quickselect"};

    int (*funcs[4]) (int *array, int length, int k) = {
        knth_nk, knth_merge, knth_n_mom, knth_n_quickselect
    };

    for (f = 1; f < 4; f++) {

        /* Instâncias A */

        for (i = 1; i < 16; i++) {
            printf("Testing: %s\n", functions[f]);
            instance_size = 1000 * pow (2, i);
            sprintf(fname, "py%d.txt", instance_size);
            original = get_data (fname, instance_size);
            instance = malloc (sizeof (int) * instance_size);

            memcpy (instance, original, sizeof (int) * instance_size);
            START(s);
            k = 5;
            number = (*funcs[f]) (instance, instance_size, k);
            assert (number == k);
            FINISH (e, s);

            memcpy (instance, original, sizeof (int) * instance_size);
            START(s);
            k = log (instance_size);
            number = (*funcs[f]) (instance, instance_size, k);
            assert (number == k);
            FINISH (e, s);

            memcpy (instance, original, sizeof (int) * instance_size);
            START(s);
            k = sqrt (instance_size);
            number = (*funcs[f]) (instance, instance_size, k);
            assert (number == k);
            FINISH (e, s);

            memcpy (instance, original, sizeof (int) * instance_size);
            START(s);
            k = instance_size / 2;
            number = (*funcs[f]) (instance, instance_size, k);
            assert (number == k);
            FINISH (e, s);

            free (instance);
        }

        /**/
        /* Istâncias Tipo B */

        for (i = 1; i < 26; i++) {
            printf("Testing: %s\n", functions[f]);
            instance_size = pow (2, 25);
            instance_swaps = pow (2, i);
            sprintf(fname, "B_%d.txt", instance_swaps);
            original = get_data (fname, instance_swaps);
            instance = malloc (sizeof (int) * instance_size);

            memcpy (instance, original, sizeof (int) * instance_size);
            START(s);
            k = 5;
            number = (*funcs[f]) (instance, instance_size, k);
            assert (number == k);
            FINISH (e, s);
            bzero (instance, sizeof (int) * instance_size);

            memcpy (instance, original, sizeof (int) * instance_size);
            START(s);
            k = log (instance_swaps);
            number = (*funcs[f]) (instance, instance_size, k);
            assert (number == k);
            FINISH (e, s);
            bzero (instance, sizeof (int) * instance_size);

            memcpy (instance, original, sizeof (int) * instance_size);
            START(s);
            current_utc_time (&s);
            k = sqrt (instance_swaps);
            number = (*funcs[f]) (instance, instance_size, k);
            assert (number == k);
            FINISH (e, s);
            bzero (instance, sizeof (int) * instance_size);

            memcpy (instance, original, sizeof (int) * instance_size);
            START(s);
            k = instance_swaps / 2;
            number = (*funcs[f]) (instance, instance_size, k);
            assert (number == k);
            FINISH (e, s);

            free (instance);
        }

    }

    return 0;
}
