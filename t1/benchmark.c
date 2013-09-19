#include <time.h>
#include <sys/time.h>

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
    int i, f, instance_size;
    int *instance;
    int k;
    int number;
    char fname[20];
    struct timespec s, e;
    long elapsed;

    char *functions[]= {"kntk_nk", "knth_merge", "knth_n_mom",
                        "knth_n_quickselect"};

    int (*funcs[4]) (int *array, int length, int k) = {
        knth_nk, knth_merge, knth_n_mom, knth_n_quickselect
    };

    for (f = 0; f < 4; f++) {
        for (i = 1; i < 16; i++) {
            printf("Testing: %s\n", functions[f]);
            instance_size = 1000 * pow (2, i);
            sprintf(fname, "py%d.txt", instance_size);
            instance = get_data (fname, instance_size);

            current_utc_time (&s);
            k = 5;
            number = (*funcs[f]) (instance, instance_size, k);
            current_utc_time (&e);
            elapsed = e.tv_nsec - s.tv_nsec;
            elapsed = elapsed / 1000000000;
            printf ("SIZE:%d %dnth is %d -- Took %lu seconds\n", instance_size,
                                                                k,
                                                                number,
                                                                elapsed);
            free (instance);

            instance = get_data (fname, instance_size);
            current_utc_time (&s);
            k = log (instance_size);
            number = (*funcs[f]) (instance, instance_size, k);
            current_utc_time (&e);
            elapsed = e.tv_nsec - s.tv_nsec;
            elapsed = elapsed / 1000000000;
            printf ("SIZE:%d %dnth is %d -- Took %lu seconds\n", instance_size,
                                                                k,
                                                                number,
                                                                elapsed);
            free (instance);

            instance = get_data (fname, instance_size);
            current_utc_time (&s);
            k = sqrt (instance_size);
            number = (*funcs[f]) (instance, instance_size, k);
            current_utc_time (&e);
            elapsed = e.tv_nsec - s.tv_nsec;
            elapsed = elapsed / 1000000000;
            printf ("SIZE:%d %dnth is %d -- Took %lu seconds\n", instance_size,
                                                                k,
                                                                number,
                                                                elapsed);
            free (instance);

            instance = get_data (fname, instance_size);
            current_utc_time (&s);
            k = instance_size / 2;
            number = (*funcs[f]) (instance, instance_size, k);
            current_utc_time (&e);
            elapsed = e.tv_nsec - s.tv_nsec;
            elapsed = elapsed / 1000000000;
            printf ("SIZE:%d %dnth is %d -- Took %lu seconds\n", instance_size,
                                                                k,
                                                                number,
                                                                elapsed);
            free (instance);
        }
    }

    return 0;
}
