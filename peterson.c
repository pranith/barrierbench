/*
 * A basic peterson lock algorithm
 */

#include <stdio.h>
#include <pthread.h>

#define USE_BARRIER 1

#define TIMES 1

#include "barrier.h"
#include "timer.h"

volatile int victim, r1, r2, wait;
volatile unsigned long counter1, counter2;
unsigned long iter = 100000000;

void *thread1(void *arg)
{
	while(wait == 0);
	for (unsigned long i = 0; i < iter; i++) {
		r1 = 1;    	// lock
		victim = 1;
		barrier();
		while(victim == 1 && r2);

		counter1++; 	// CS
		r1 = 0;		// unlock
		barrier();
	}

	return NULL;
}

void *thread2(void *arg)
{
	while(wait == 0);
	for (unsigned long i = 0; i < iter; i++) {
		r2 = 1;		// lock
		victim = 2;
		barrier();
		while(victim == 2 && r1);

		counter2++; 	// CS
		r2 = 0;		// unlock
		barrier();
	}

	return NULL;
}

int main()
{
	pthread_t tid1, tid2;
	struct timespec before, after;
	clockid_t cid;

	if (clock_getcpuclockid(0, &cid))
		fprintf(stderr, "unreliable clock source\n");

	for (int i = 0; i < TIMES; i++) {
		counter1 = 0;
		counter2 = 0;
		start_watch(&before);
		pthread_create(&tid1, NULL, thread1, NULL);
		pthread_create(&tid2, NULL, thread2, NULL);
		wait = 1;

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		stop_watch(&after);
		barrier();
		printf("counter is %lu, time: %ld\n", counter1 + counter2, get_timer_diff(&before, &after));
	}

	return 0;
}
