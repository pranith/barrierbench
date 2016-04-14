/* reading from the same location to different destination locations
 *
 * Author: Pranith Kumar
 */

#define ACC_DEBUG 0

#if ACC_DEBUG
#define myprintf(...) printf(__VA_ARGS__)
#define NUM_ITER 1
#define REPEAT 1
#else
#define myprintf(...) 
#define NUM_ITER 1000
#define REPEAT 1
#endif

#include <stdio.h>
#include <stdlib.h>

#define USE_BARRIER 1
#include "../barrier.h"
#include "../timer.h"
#include "common.h"

long *src, *src1;
long result;
unsigned long size;
//unsigned long repeat, num_iter = NUM_ITER; //5000000016 / num_mem_ops;

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

void warmup(int val)
{
  unsigned long j, i;

  size = MB(64) / sizeof(long);
  if (!src)
	  src = (long *)malloc(sizeof(long) * size);

  src1 = (long *)malloc(sizeof(long) * size);

  //initialize array
  for (i = 0; i < 5; i++)
  for (j = 0; j < size; j++)
    src1[j] = 8 * val;

  free(src1);
}

void flush_cache(void)
{
  size = MB(64) / sizeof(long);
  int offset = CACHE_LINE_SIZE / sizeof(long);
  for (int j = 0; j < size; j+=offset)
    flush(src+j);
}

#pragma GCC optimize ("unroll-loops")
int main(int argc, char* argv[])
{
  //warmup(0);
  unsigned long j, i = 0;
  volatile long dest = 0;
  int num_req = 0;

  src = (long *)malloc(MB(64));
  if (argc > 1)
	  num_req = atoi(argv[1]);

  struct timespec before, after;
  unsigned long timer = 0;

  //printf("%lu, ", num_iter * num_req * 5);

  for (int repeat = 0; repeat < REPEAT; repeat++) {
	  flush_cache();
	  for(j = 0; j < NUM_ITER; j++)
	  {
		  start_watch(&before);
		  #include "defines.h"
		  // flush write buffer
		  barrier();
		  stop_watch(&after);

		  i += 8 + dest;

		  if (i + indexarr63 >= size)
			  i = 0;

		  timer += get_timer_diff(&before, &after);
	  }

    printf("%d, %ld\n", num_req, timer);
    timer = 0;
    //warmup(repeat);
  }


  fflush(NULL);
  return 0;
}
