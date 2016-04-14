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
volatile long dest = 16;

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

void warmup()
{
  unsigned long j;
  max_index = MB(MEM_SIZE) / sizeof(long);
  src = (long *)malloc(sizeof(long) * max_index);
  //initialize array
  /*
  for (j = 0; j < max_index; j++)
    src[j] = 16;
    */
}


int main(int argc, char* argv[])
{
  warmup();
  unsigned long j, i = 0;
  int num_req = 0;
  int mem_region_size = NUM_ACCESSES_PER_ITER * CACHE_LINE_SIZE * 2;
  int iter_offset = mem_region_size / sizeof(long);
  int max_repeat = 3;

  if (argc > 1)
	  num_req = atoi(argv[1]);
  if (argc > 2)
	  max_repeat = atoi(argv[2]);


  unsigned long repeat, num_iter = NUM_ITER;
  struct timespec before, after;
  unsigned long tot_time = 0;

  printf("%lu,%d,", num_iter * num_req,num_req);
  for (repeat = 0; repeat < max_repeat; repeat++) {
	  tot_time = 0;
	  for(j = 0; j < num_iter; j++)
	  {

		  #include "flush.h"
		  start_watch(&before);
		  #include "defines.h"
		  //barrier();
		  stop_watch(&after);
		  tot_time += get_timer_diff(&before, &after);

		  i += iter_offset;

		  if (i + iter_offset > max_index)
			  i = 0;
	  }
	  printf("%ld,", tot_time);
  }
  printf("\n");

  //printf("cache accesses %ld, cache misses %ld\n", num_iter * NUM_ACCESSES_PER_ITER, num_iter * num_req);
  //fprintf(stderr, "%ld\n", dest);

  fflush(NULL);
  return 0;
}
