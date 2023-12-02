#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char digit(char *str)
{
	size_t len = strlen(str);
	if (*str >= '0' && *str <= '9') return *str;
#define DIGIT_IS(_len, _str) (len >= _len && !strncmp(str, _str, _len))
	if (DIGIT_IS(3, "one"))   return '1';
	if (DIGIT_IS(3, "two"))   return '2';
	if (DIGIT_IS(5, "three")) return '3';
	if (DIGIT_IS(4, "four"))  return '4';
	if (DIGIT_IS(4, "five"))  return '5';
	if (DIGIT_IS(3, "six"))   return '6';
	if (DIGIT_IS(5, "seven")) return '7';
	if (DIGIT_IS(5, "eight")) return '8';
	if (DIGIT_IS(4, "nine"))  return '9';
	return 0;
}

int main(void)
{
	int sum = 0, d, i;
	char buf[BUFSIZ], number[3] = {0};
	while (fgets(buf, sizeof(buf), stdin)) {
		for (i = 0; buf[i]; i++) {
			if (!(d = digit(buf + i))) {
				continue;
			}
			if (!number[0]) number[0] = d;
			number[1] = d;
		}
		sum += atoi(number);
		number[0] = 0;
	}
	printf("%d\n", sum);
	return 0;
}
/* 54770 */
