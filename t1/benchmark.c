#include <time.h>
#include <sys/time.h>

#include "paa.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif


int main (int argc, char **argv)
{
    int i, instance_size;
    int *instance;
    struct timespec start, end;

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    start.tv_sec = mts.tv_sec;
    start.tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, &start);
#endif


    for (i = 0; i < 12; i++) {
        srand (time (NULL));
        instance_size = 1000 * pow (2, i);
        instance = gen_instance_type1 (instance_size);
        knth_nk (instance, instance_size, 500);
        free (instance);
    }

    return 0;
}
