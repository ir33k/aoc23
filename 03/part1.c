#include <stdio.h>
#include <stdlib.h>

#define SIZ 256
#define SIZ_2 (SIZ*SIZ)
#define DIGIT(c) ((c) >= '0' && (c) <= '9')

static int taken(int *ip)
{
	static int *taken[SIZ_2];
	static int siz = 0;
	int i;
	for (i = 0; i < siz; i++) {
		if (taken[i] == ip) {
			return 1;
		}
	}
	taken[siz++] = ip;
	return 0;
}

int main(void)
{
	long int sum = 0;
	char buf[BUFSIZ];
	char symbol[SIZ_2] = {0};
	int  number[SIZ_2] = {0};
	int *nump;
	int *part[SIZ_2]   = {0};
	int i; /* Index to symbol and part arrays, x+y*w */
	int x,y, num, parti, j,k;
	for (y = 0; fgets(buf, sizeof(buf), stdin); y++) {
		i = y*SIZ;
		for (x = 0; buf[x] != '\n'; x++, i++) {
			if (buf[x] == '.') {
				continue;
			}
			if (DIGIT(buf[x])) {
				num = atoi(&buf[x]);
				number[i] = num;
				nump = &number[i];
				part[i] = nump;
				for (; DIGIT(buf[x]); x++, i++) {
					part[i] = nump;
				}
				x--;
				i--;
				continue;
			}
			symbol[i] = buf[x];
		}
	}
	for (i = 0; i < SIZ_2; i++) {
		if (!symbol[i]) {
			continue;
		}
		x = i % SIZ;
		y = i / SIZ;
		if (x > 0) x--;
		if (y > 0) y--;
		for (k = x+3, j = y+3; y < j; y++, x-=3)
		for (; x < k; x++) {
			parti = y*SIZ + x;
			if (parti == i) {
				continue;
			}
			if (!part[parti]) {
				continue;
			}
			if (taken(part[parti])) {
				continue;
			}
			sum += *part[parti];
		}
	}
	printf("%ld\n", sum);
	return 0;
}
