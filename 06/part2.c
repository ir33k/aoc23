#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long long unsigned str2num(char *str)
{
	long long unsigned num = 0;
	size_t i, len = strlen(str);
	for (i = 0; i < len; i++) {
		num += str[i] - '0';
		if (i+1 < len) {
			num *= 10;
		}
	}
	return num;
}

int main(void)
{
	char buf[BUFSIZ], *bp, number[32] = {0};
	long long unsigned i, time, distance, travel;
	long long unsigned win = 0;
	bp = fgets(buf, sizeof(buf), stdin);
	bp = strchr(buf, ':') + 1;
	for (i = 0; *bp != '\n'; bp++) {
		if (*bp == ' ') {
			continue;
		}
		number[i++] = *bp;
	}
	time = str2num(number);
	bp = fgets(buf, sizeof(buf), stdin);
	bp = strchr(buf, ':') + 1;
	for (i = 0; *bp != '\n'; bp++) {
		if (*bp == ' ') {
			continue;
		}
		number[i++] = *bp;
	}
	distance = str2num(number);
	for (i = 1; i < time; i++) {
		travel = (time - i) * i;
		if (travel > distance) {
			win++;
		}
	}
	printf("%llu\n", win);
	return 0;
}
