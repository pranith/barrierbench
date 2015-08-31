#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include "timer.h"

#include "barrier.h"

unsigned long counter = 0;
unsigned long iter = 100000000;

/* Increment the value pointed by ptr */
#define atomic_inc(ptr, lock)		  \
  ({					  \
    asm volatile (lock " incl %0;\n"       \
		  : "+m"(*ptr));	  \
  })

void *thread1(void *arg)
{
	for (unsigned long i = 0; i < iter; i++)
	  atomic_inc(&counter, "");

	return NULL;
}

void *thread2(void *arg)
{
	for (unsigned long i = 0; i < iter; i++)
	  atomic_inc(&counter, "lock");

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
		counter = 0;
		start_watch(&before);
		if (i % 2) {
		  pthread_create(&tid1, NULL, thread1, NULL);
		  pthread_create(&tid2, NULL, thread1, NULL);
		} else {
		  pthread_create(&tid1, NULL, thread2, NULL);
		  pthread_create(&tid2, NULL, thread2, NULL);
		}

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		stop_watch(&after);
		//printf("counter is %lu, time: %ld\n", counter, get_timer_diff(&before, &after));
		printf("%ld, ", get_timer_diff(&before, &after));
		if (i % 2)
		  printf("\n");

	}

	return 0;
}
