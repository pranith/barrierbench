/* reading from the same location to different destination locations
 *
 * Author: Pranith Kumar
 */


#include <stdio.h>
#include <stdlib.h>

#define USE_BARRIER 1
#include "../barrier.h"
#include "../timer.h"

long *src;
long result;
unsigned long size;

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

void warmup()
{
  unsigned long j;
  size = MB(64) / sizeof(long);
  src = (long *)malloc(sizeof(long) * size);
  //initialize array
  for (j = 0; j < size; j++)
    src[j] = 8;
}


int main(int argc, char* argv[])
{
  warmup();
  unsigned long j, i = 0;
  volatile long dest = 0;
  int num_mem_ops = 400;
  int num_req = 0;

  if (argc > 1)
	  num_req = atoi(argv[1]);

  unsigned long repeat, num_iter = 5000000000 / num_mem_ops;
  struct timespec before, after;

  printf("%lu, ", num_iter * num_req * 5);

  start_watch(&before);
  for (repeat = 0; repeat < 5; repeat++) {
	  for(j = 0; j < num_iter; j++)
	  {
		  #include "defines.h"
		  // flush write buffer
		  barrier();

		  i += 8 + dest;

		  if (i + indexarr399 > size)
			  i = 0;
	  }
  }
  stop_watch(&after);

  printf("%d, %ld\n", num_req, get_timer_diff(&before, &after));

  fflush(NULL);
  return 0;
}
