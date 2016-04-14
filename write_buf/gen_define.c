#include <stdio.h>
#include <stdlib.h>

#define CACHE_LINE_SIZE 64
#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

#define NUM_REQ 64

int main(int argc, char *argv[])
{
	int i = 0, num_req = 1;
	int cache_size = MB(64);
	int max_index = cache_size / sizeof(long);
	unsigned long j = 0;
	int *indexarr = (int *)malloc(sizeof(int) * NUM_REQ);

	if (argc > 1)
		num_req = atoi(argv[1]);

	if (num_req == 0)
		return 0;

	int period = NUM_REQ / num_req;
	int offset = cache_size / (num_req * sizeof(long));

	int ind = 0;
	for (j = 0; j < NUM_REQ; j++)
	{
		//indexarr[j] = /*(num_req * j) / 50 +*/ (num_req * j * offset) / 400;
		indexarr[j] = ind;
		if (i >= period)
		{
			i = 0;
			ind += offset;
			if (ind > max_index)
				ind -= offset;
		}
		i++;
	}

	for (i = 0; i < NUM_REQ; i++) {
		printf("src[i + %d] = dest;\n", indexarr[i]);
		printf("myprintf\(\"Accessing %%lu\\n\", i + %d);\n", indexarr[i]); 
	}

	printf("#define indexarr%d %d\n", NUM_REQ - 1, indexarr[NUM_REQ - 1]);

	return 0;
}
