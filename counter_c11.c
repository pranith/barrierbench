#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include "timer.h"

#include "barrier.h"

_Atomic unsigned long counter = 0;
unsigned long iter = 100000000;

void run_counter()
{
	for (unsigned long i = 0; i < iter; i++) {
		unsigned long temp1, temp2;
		__atomic_load(&counter, &temp2, __ATOMIC_ACQUIRE);
		__atomic_load(&counter, &temp1, __ATOMIC_ACQUIRE);
		temp1 = temp1+1;
		temp2 = temp2+1;
		__atomic_store(&counter, &temp2, __ATOMIC_RELEASE);
		__atomic_store(&counter, &temp1, __ATOMIC_RELEASE);
	}
}

int main()
{
	struct timespec before, after;
	clockid_t cid;

	if (clock_getcpuclockid(0, &cid))
		fprintf(stderr, "unreliable clock source\n");

	for (int i = 0; i < 20; i++) {
		counter = 0;
		start_watch(&before);
		run_counter();
		stop_watch(&after);
		//printf("counter is %lu, time: %ld\n", counter, get_timer_diff(&before, &after));
		printf("%ld\n", get_timer_diff(&before, &after));

	}

	return 0;
}
