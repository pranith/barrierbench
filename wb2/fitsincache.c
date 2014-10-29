/* reading from the same location to different destination locations
 *
 * Author: Pranith Kumar
 */


#include <stdio.h>
#include <stdlib.h>

//#define USE_BARRIER 1
#include "../barrier.h"
#include "../timer.h"
#include "common.h"

long *src;
long result;
unsigned long max_index;

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

void warmup()
{
  unsigned long j;
  max_index = MB(MEM_SIZE) / sizeof(long);
  src = (long *)malloc(sizeof(long) * max_index);
  //initialize array
  for (j = 0; j < max_index; j++)
    src[j] = 16;
}


int main(int argc, char* argv[])
{
  warmup();
  unsigned long j, i = 0;
  volatile long dest = 0;
  int num_req = 0;

  if (argc > 1)
	  num_req = atoi(argv[1]);

  unsigned long repeat, num_iter = NUM_ITER;
  struct timespec before, after;


  int max_repeat = 3;
  printf("%lu,%d,", num_iter * num_req,num_req);
  for (repeat = 0; repeat < max_repeat; repeat++) {
	  start_watch(&before);
	  for(j = 0; j < num_iter; j++)
	  {
		  #include "defines.h"
		  // flush write buffer
		  barrier();

		  i += 32 + dest;

		  if (i + lastindex > max_index)
			  i = 0;
	  }
	  stop_watch(&after);
	  printf("%ld,", get_timer_diff(&before, &after));
  }
  printf("\n");

  //printf("cache accesses %ld, cache misses %ld\n", num_iter * NUM_ACCESSES_PER_ITER, num_iter * num_req);
  //fprintf(stderr, "%ld\n", dest);

  fflush(NULL);
  return 0;
}
