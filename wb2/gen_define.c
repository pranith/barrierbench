#include <stdio.h>
#include <stdlib.h>

#define CACHE_LINE_SIZE 64
#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

int main(int argc, char *argv[])
{
	int i = 0, num_req = 1;
	int cache_size = MB(64);
	int max_index = cache_size / sizeof(long);
	unsigned long j = 0;
	int *indexarr = (int *)malloc(sizeof(int) * 400);

	if (argc > 1)
		num_req = atoi(argv[1]);

	if (num_req == 0)
		return 0;

	int period = 400 / num_req;
	int offset = cache_size / (num_req * sizeof(long));

	int ind = 0;
	for (j = 0; j < 400; j++)
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

	for (i = 0; i < 400; i++)
		printf("dest = src[i + %d];\n", indexarr[i]);

	printf("#define indexarr399 %d\n", indexarr[399]);

	return 0;
}
