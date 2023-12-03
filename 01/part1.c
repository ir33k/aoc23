#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int sum = 0;
	char c, number[3] = {0};
	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			sum += atoi(number);
			number[0] = 0;
			continue;
		}
		if (c >= '0' && c <= '9') {
			if (!number[0]) number[0] = c;
			number[1] = c;
		}
	}
	printf("%d\n", sum);
	return 0;
}
/* 54630 */
