#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *skip(char *bp, char c)
{
	while (*bp == c) bp++;
	return bp;
}

static int has(int *arr, int v)
{
	int i;
	for (i = 0; arr[i]; i++) {
		if (arr[i] == v) {
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	int i, arr[32], points, sum = 0;
	char buf[BUFSIZ], *bp;
	while (fgets(buf, sizeof(buf), stdin)) {
		memset(arr,  0, sizeof(arr));
		points = 0;
		bp = buf;
		bp = strpbrk(bp, ":");
		bp = strpbrk(bp, " ");
		bp = skip(bp, ' ');
		for (i = 0; *bp != '|'; i++) {
			arr[i] = atoi(bp);
			bp = strpbrk(bp, " ");
			bp = skip(bp, ' ');
		}
		while (*bp != '\n') {
			if (has(arr, atoi(bp))) {
				points = points ? points*2 : 1;
			}
			bp = strpbrk(bp, " \n");
			bp = skip(bp, ' ');
		}
		sum += points;
	}
	printf("%d\n", sum);
	return 0;
}
