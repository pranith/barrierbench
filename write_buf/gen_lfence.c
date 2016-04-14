#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

void generate_randindices(int *randindices)
{
	int i = 0;
	for (i = 0; i < NUM_ACCESSES_PER_ITER; i++)
		randindices[i] = -1;

	srandom(time(NULL));

	i = 0;
	while(i != NUM_ACCESSES_PER_ITER) {
		int rand_index = random() % NUM_ACCESSES_PER_ITER;
		if (randindices[rand_index] == -1) {
			randindices[rand_index] = i;
			i++;
		}
	}

	return;
}

int main(int argc, char *argv[])
{
	int i = 0, num_misses_per_iter = NUM_MISSES_PER_ITER;
	int cache_size = MB(MEM_SIZE);
	int num_cache_lines = cache_size / CACHE_LINE_SIZE;
	int max_index = cache_size / sizeof(long);
	unsigned long j = 0;
	int *indexarr = (int *)malloc(sizeof(int) * NUM_ACCESSES_PER_ITER);
	int *randindices = (int *)malloc(sizeof(int) * NUM_ACCESSES_PER_ITER);

	FILE *defines, *flush;

	defines = fopen("defines.h", "w");
	flush = fopen("flush.h", "w");
	if (argc > 1)
		num_misses_per_iter = atoi(argv[1]);

	if (num_misses_per_iter == 0)
		return 0;

	// increment index after every 'period' accesses
	int period = NUM_ACCESSES_PER_ITER / num_misses_per_iter;

	// increment index by offset for every 'period' accesses
	int offset = 2 * CACHE_LINE_SIZE / sizeof(long); //cache_size / (num_misses_per_iter * sizeof(long));
	int max_offset = NUM_ACCESSES_PER_ITER * 2 * CACHE_LINE_SIZE / sizeof(long);

	int ind = 0, max;
	for (j = 0; j < NUM_ACCESSES_PER_ITER; j++)
	{
		//indexarr[j] = /*(num_misses_per_iter * j) / 50 +*/ (num_misses_per_iter * j * offset) / num_misses_per_iter;
		indexarr[j] = ind;
		i++;
		if (i >= period)
		{
			i = 0;
			ind += offset;
			if (ind >= max_offset) {
				ind = 0;
				max = ind - offset;
			}
		}
	}

	// shuffle indices
	generate_randindices(randindices);

	for (i = 0; i < NUM_ACCESSES_PER_ITER; i++) {
		fprintf(defines, "src[i + %d] = dest;\n", indexarr[randindices[i]]);
		fprintf(defines, "myprintf\(\"Accessing %%lu\\n\", i + %d);\n", indexarr[randindices[i]]); 
	}
	fprintf(defines, "barrier();\n");
	fprintf(defines, "#define indexarr%d %d\n", NUM_ACCESSES_PER_ITER - 1, max);

	fclose(defines);
	fclose(flush);

	return 0;
}
