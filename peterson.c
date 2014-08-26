/*
 * A basic peterson lock algorithm
 */

#include <stdio.h>
#include <pthread.h>

#define USE_BARRIER 1
#include "barrier.h"

int victim, r1, r2, counter;

void *thread1(void *arg)
{
	r1 = 1;
	victim = 1;
	barrier();
	while(victim == 1 && r2);

	counter++; // CS
	r1 = 0;
	write_barrier();

	return NULL;
}

void *thread2(void *arg)
{
	r2 = 1;
	victim = 2;
	barrier();
	while(victim == 1 && r1);

	counter++; // CS
	r2 = 0;
	write_barrier();

	return NULL;
}

int main()
{
	pthread_t tid1, tid2;

	for (int i = 0; i < 1000000; i++) {
		pthread_create(&tid1, NULL, thread1, NULL);
		pthread_create(&tid2, NULL, thread2, NULL);

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
	}

	printf("counter is %d\n", counter);

	return 0;
}
