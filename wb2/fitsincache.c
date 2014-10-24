/* reading from the same location to different destination locations
 *
 * Author: Pranith Kumar
 */


#include <stdio.h>
#include <stdlib.h>

#define USE_BARRIER 0
#include "../barrier.h"
#include "../timer.h"

#define MEM_SIZE 128
#define NUM_ACCESSES_PER_ITER 400

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

  unsigned long repeat, num_iter = 10000000;
  struct timespec before, after;


  start_watch(&before);
  for (repeat = 0; repeat < 1; repeat++) {
	  for(j = 0; j < num_iter; j++)
	  {
		  #include "defines.h"
		  // flush write buffer
		  barrier();

		  i += 32 + dest;

		  if (i + lastindex > max_index)
			  i = 0;
	  }
  }
  stop_watch(&after);

  printf("cache accesses %ld, cache misses %ld\n", num_iter * NUM_ACCESSES_PER_ITER, num_iter * num_req);
  printf("%lu, ", num_iter * num_req * repeat);
  printf("%d, %ld\n", num_req, get_timer_diff(&before, &after));
  fprintf(stderr, "%ld\n", dest);

  fflush(NULL);
  return 0;
}
