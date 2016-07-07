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
#define NUM_ITER 100000
#define REPEAT 10
#endif

#include <stdio.h>
#include <stdlib.h>

#define USE_BARRIER 1
#include "../barrier.h"
#include "common.h"

volatile long *src, *src1;
long result;
unsigned long size;
//unsigned long repeat, num_iter = NUM_ITER; //5000000016 / num_mem_ops;

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

void warmup(int val)
{
  unsigned long j, i;

  size = MB(MEM_SIZE) / sizeof(long);
  if (!src)
    src = (long *)malloc(sizeof(long) * size);

  src1 = (long *)malloc(sizeof(long) * size);

  //initialize array
  for (i = 0; i < 5; i++) {
    for (j = 0; j < size; j++) {
      src1[j] = 8 * val;
      src[j]  = 8;
    }
  }

  free(src1);
}

void flush_cache(void)
{
  size = MB(MEM_SIZE) / sizeof(long);
  int offset = CACHE_LINE_SIZE / sizeof(long);
  for (int j = 0; j < size; j+=offset)
    flush(src+j);
}

#pragma GCC optimize ("unroll-loops")
int main(int argc, char* argv[])
{
  //warmup(0);
  volatile long dest = 32;
  int num_req = 0;

  src = (long *)malloc(MB(MEM_SIZE));
  if (argc > 1)
	  num_req = atoi(argv[1]);

  struct timespec before, after;
  unsigned long timer = 0;

  flush_cache();
  for (int repeat = 0; repeat < REPEAT; repeat++) {
    unsigned long j, i = 0, i_start = 0;
    for(j = 0; j < NUM_ITER; j++)
    {
      #include "defines.h"
      // flush write buffer
      // barrier();

      i += 8 + src[indexarr39 + i];

      if (i + indexarr39 >= size) {
	      myprintf("Resetting...\n");
	      i_start += 8;
        i = i_start;
      }
    }
    //flush_cache();
  }

  fflush(NULL);
  return 0;
}
