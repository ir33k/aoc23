#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARDSIZ 256

static int s_card[CARDSIZ] = {0};

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

static int carddo(int i)
{
	int res = s_card[i] + 1;
	int end = i + res;
	int sum = 1;
	for (i++; i < end; i++) {
		sum += carddo(i);
	}
	return sum;
}

int main(void)
{
	int ci;
	int i, arr[32], sum = 0, arrsiz = 0;
	char buf[BUFSIZ], *bp;
	for (ci = 0; fgets(buf, sizeof(buf), stdin); ci++) {
		memset(arr,  0, sizeof(arr));
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
				s_card[ci]++;
			}
			bp = strpbrk(bp, " \n");
			bp = skip(bp, ' ');
		}
		arrsiz++;
	}
	for (i = 0; i < arrsiz; i++) {
		sum += carddo(i);
	}
	printf("%d\n", sum);
	return 0;
}
