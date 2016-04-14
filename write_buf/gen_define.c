#include <stdio.h>
#include <stdlib.h>

#define CACHE_LINE_SIZE 64
#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

#define TOT_REQ 64

int main(int argc, char *argv[])
{
	int i = 0, num_req = 1;
	int cache_size = MB(64);
	int max_index = cache_size / sizeof(long);
	unsigned long j = 0;
	int *indexarr = (int *)malloc(sizeof(int) * TOT_REQ);

	if (argc > 1)
		num_req = atoi(argv[1]);

	if (num_req == 0)
		return 0;

	int period = TOT_REQ / num_req;
	int offset = cache_size / (num_req * sizeof(long));
  printf("offset is %d\n", offset);

	int ind = 0, max;
	for (j = 0; j < period; j++)
	{
		for (int k = 0; k < num_req; k++) {
			indexarr[j+k*period] = ind;
		}
		ind += offset;
		if (ind >= max_index) {
			max = ind - offset;
			ind = 0;
		}
	}

	for (i = 0; i < TOT_REQ; i++) {
		printf("src[i + %d] = dest;\n", indexarr[i]);
		printf("myprintf\(\"Accessing %%lu\\n\", i + %d);\n", indexarr[i]); 
	}

	printf("#define indexarr%d %d\n", TOT_REQ - 1, max);

	return 0;
}
