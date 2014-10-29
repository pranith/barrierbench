#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define CACHE_LINE_SIZE 64

int main(int argc, char *argv[])
{
	int i = 0, num_misses_per_iter = NUM_MISSES_PER_ITER;
	int cache_size = MB(MEM_SIZE);
	int max_index = cache_size / sizeof(long);
	unsigned long j = 0;
	int *indexarr = (int *)malloc(sizeof(int) * NUM_ACCESSES_PER_ITER);

	if (argc > 1)
		num_misses_per_iter = atoi(argv[1]);

	if (num_misses_per_iter == 0)
		return 0;

	// increment index after every 'period' accesses
	int period = NUM_ACCESSES_PER_ITER / num_misses_per_iter;

	// increment index by offset for every 'period' accesses
	int offset = cache_size / (num_misses_per_iter * sizeof(long));

	int ind = 0;
	for (j = 0; j < NUM_ACCESSES_PER_ITER; j++)
	{
		//indexarr[j] = /*(num_misses_per_iter * j) / 50 +*/ (num_misses_per_iter * j * offset) / num_misses_per_iter;
		indexarr[j] = ind;
		i++;
		if (i >= period)
		{
			i = 0;
			ind += offset;
			if (ind >= max_index)
				ind -= offset;
		}
	}

	for (i = 0; i < NUM_ACCESSES_PER_ITER; i++)
		printf("dest = src[i + %d];\n", indexarr[i]);

	printf("#define lastindex %d\n", indexarr[NUM_ACCESSES_PER_ITER-1]);

	return 0;
}
