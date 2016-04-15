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
	int i = 0, num_misses_per_iter = NUM_ACCESSES_PER_ITER;
	int cache_size = MB(MEM_SIZE);
	unsigned long j = 0;
	int *indexarr = (int *)malloc(sizeof(int) * NUM_ACCESSES_PER_ITER);
	int *randindices = (int *)malloc(sizeof(int) * NUM_ACCESSES_PER_ITER);

	FILE *defines;

	defines = fopen("defines.h", "w");
	if (argc > 1)
		num_misses_per_iter = atoi(argv[1]);

	if (num_misses_per_iter == 0)
		return 0;

	// increment index after every 'period' accesses
	int period = NUM_ACCESSES_PER_ITER / num_misses_per_iter;
	if (period * num_misses_per_iter < NUM_ACCESSES_PER_ITER)
		period++;

	// increment index by offset for every 'period' accesses
	int offset = cache_size / (num_misses_per_iter * sizeof(long));
	if (offset * num_misses_per_iter * sizeof(long) < cache_size)
		offset++;

	int max_index = cache_size / sizeof(long);
	printf("Offset is %d, period is %d, max_idx %d\n", offset, period, max_index);

	int ind = 0, max = 0;
	for (j = 0; j < num_misses_per_iter; j++)
	{
		for (int k = 0; k < period; k++) {
			indexarr[j+k*num_misses_per_iter] = ind;
		}
		ind += offset;
		if (ind >= max_index) {
			ind = 0;
		}
		if (ind > max) {
			max = ind;
		}
	}

	// shuffle indices
	generate_randindices(randindices);

	for (i = 0; i < NUM_ACCESSES_PER_ITER; i++) {
		//printf("src[i + %d] = dest;\n", indexarr[i]);
		//fprintf(defines, "flush(src+i+%d);\n", indexarr[randindices[i]]);
		fprintf(defines, "src[i + %d] = dest;\n", indexarr[randindices[i]]);
		//fprintf(defines, "barrier();\n");
		//fprintf(defines, "flush(src+i+%d);\n", indexarr[randindices[i]]);
		//fprintf(defines, "myprintf\(\"Accessing %%lu\\n\", i + %d);\n", indexarr[randindices[i]]); 
	}
	//fprintf(defines, "barrier();\n");
	fprintf(defines, "#define indexarr%d %d\n", NUM_ACCESSES_PER_ITER - 1, max);

	//fclose(defines);

	return 0;
}
