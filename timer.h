#include <time.h>

#define DEBUG 0

unsigned long long get_timer_nsec(struct timespec *timer)
{
	return timer->tv_sec * 1E6 + timer->tv_nsec / 1000;
}

long get_timer_diff(struct timespec *before, struct timespec *after)
{
	return get_timer_nsec(after) - get_timer_nsec(before);
}

void start_watch(struct timespec *timer)
{
	if (clock_gettime(CLOCK_MONOTONIC, timer))
		fprintf(stderr, "startWatch failed\n");

#if DEBUG
	printf("time val is %llu\n", get_timer_nsec(timer));
#endif
}

void stop_watch(struct timespec *timer)
{
	return start_watch(timer);
}
