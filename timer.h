#include <sys/time.h>

void start_watch(struct timeval *timer)
{
	if (gettimeofday(timer, NULL))
		fprintf(stderr, "startWatch failed\n");
}

void stop_watch(struct timeval *timer)
{
	if (gettimeofday(timer, NULL))
		fprintf(stderr, "startWatch failed\n");
}

long get_timer_usec(struct timeval *timer)
{
	return timer->tv_sec * 1E6 + timer->tv_usec;
}

long get_timer_diff(struct timeval *before, struct timeval *after)
{
	return get_timer_usec(after) - get_timer_usec(before);
}
