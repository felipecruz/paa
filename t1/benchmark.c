#include <time.h>
#include <sys/time.h>

#define START(s) current_utc_time (&s)
#define FINISH(e, s)                                                        \
    current_utc_time (&e);                                                  \
    elapsed = timespecDiff (&e, &s);                                        \

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
    int instance_size, instance_swaps;
    int *instance, *original;
    int k;
    int number;
    int algo;
    int type;
    int instance_number;

    char instance_type;
    char fname[20];
    char *functions[]= {"kntk_nk", "knth_merge", "knth_n_mom",
                        "knth_n_quickselect"};
    long elapsed;
    struct timespec s, e;

    int (*funcs[4]) (int *array, int length, int k) = {
        knth_nk, knth_merge, knth_n_mom, knth_n_quickselect
    };

    if (argc < 4) {
        printf("./benchmark algo_index{nk,merge,mom,quick}"
               "k{1=5,2=log,3=sqrt,4=n/2} type{1=A,2=B} instance_number\n");
        return 0;
    }

    algo = atoi (argv[1]);
    algo--;

    k = atoi (argv[2]);
    type = atoi (argv[3]);
    instance_number = atoi (argv[4]);

    if (type == 1) {
        instance_size = 1000 * pow (2, instance_number);
        sprintf(fname, "py%d.txt", instance_size);
        original = get_data (fname, instance_size);
        instance = malloc (sizeof (int) * instance_size);
        instance_type = 'A';
    } else {
        instance_size = pow (2, 25);
        instance_swaps = pow (2, instance_number);
        sprintf(fname, "B_%d.txt", instance_swaps);
        original = get_data (fname, instance_size);
        instance = malloc (sizeof (int) * instance_size);
        instance_type = 'B';
    }

    if (k == 1)
        k = 5;
    if (k == 2)
        k = log (instance_size);
    if (k == 3)
        k = sqrt (instance_size);
    if (k == 4)
        k = instance_size / 2;

    memcpy (instance, original, sizeof (int) * instance_size);
    START(s);
    number = (*funcs[algo]) (instance, instance_size, k);
    assert (number == k);
    FINISH (e, s);

    printf("%s;", functions[algo]);
    printf("%d;", instance_size);
    printf("%d;", k);
    printf("%c;", instance_type);
    printf("%d;", instance_number);
    printf("%ld\n", elapsed);

    free (instance);
    free (original);

    return 0;
}
