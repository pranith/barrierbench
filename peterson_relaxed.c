/*
 * A basic peterson lock algorithm
 */

#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#include "timer.h"

atomic_int victim, r1, r2, wait;
volatile unsigned long counter1, counter2, counter;
unsigned long iter = 1000000;

void *thread1(void *arg)
{
	while(atomic_load_explicit(&wait, memory_order_relaxed) == 0);
	for (unsigned long i = 0; i < iter; i++) {
		atomic_exchange_explicit(&r1, 1, memory_order_relaxed);    	// lock
		atomic_exchange_explicit(&victim, 1, memory_order_relaxed);
		while(atomic_load_explicit(&victim, memory_order_relaxed) == 1 
				&& atomic_load_explicit(&r2, memory_order_relaxed));

		counter++; 	// CS
		atomic_store_explicit(&r1, 0, memory_order_release);
	}

	return NULL;
}

void *thread2(void *arg)
{
	while(atomic_load_explicit(&wait, memory_order_relaxed) == 0);
	for (unsigned long i = 0; i < iter; i++) {
		atomic_exchange_explicit(&r2, 1, memory_order_relaxed);    	// lock
		atomic_exchange_explicit(&victim, 2, memory_order_relaxed);
		while(atomic_load_explicit(&victim, memory_order_relaxed) == 2 
				&& atomic_load_explicit(&r1, memory_order_relaxed));

		counter++; 	// CS
		atomic_store_explicit(&r2, 0, memory_order_release);
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

	for (int i = 0; i < 20; i++) {
		counter1 = 0;
		counter2 = 0;
		counter  = 0;
		start_watch(&before);
		pthread_create(&tid1, NULL, thread1, NULL);
		pthread_create(&tid2, NULL, thread2, NULL);

		atomic_store_explicit(&wait, 1, memory_order_relaxed);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		stop_watch(&after);
		printf("counter is %lu, time: %ld\n", counter1+counter2, get_timer_diff(&before, &after));
	}

	return 0;
}
