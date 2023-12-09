#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { LEFT=0, RIGHT, END };

static int index_of(char *arr[], char *find)
{
	int i;
	for (i = 0; arr[i]; i++) {
		if (!strcmp(arr[i], find)) {
			return i;
		}
	}
	return -1;
}

int main(void)
{
	char c, buf[16*1024], *key[1024];
	size_t len, lr_max;
	unsigned i, j;
	short node[sizeof(key)][3] = {0};
	short lr[BUFSIZ], beg;
	long long unsigned res;
	for (i = 0; (c = fgetc(stdin)) != '\n'; i++) {
		lr[i] = c == 'R' ? RIGHT : LEFT;
	}
	lr_max = i;
	fgets(buf, sizeof(buf), stdin);
	for (len = 0; (i = fread(buf, 1, sizeof(buf), stdin)); len += i);
	buf[len] = 0;
	for (i = 0, j = 0; buf[j]; j += 17) {
		buf[j +  3] = 0;
		buf[j + 10] = 0;
		buf[j + 15] = 0;
		if (!strcmp(buf + j, "AAA")) {
			beg = i;
		}
		node[i][END] = !strcmp(buf + j, "ZZZ");
		key[i++] = buf + j;
	}
	for (i = 0, j = 0; buf[j]; j += 17, i++) {
		node[i][LEFT]  = index_of(key, buf + j + 7);
		node[i][RIGHT] = index_of(key, buf + j + 12);
	}
	for (i = beg, res = 0; !node[i][END]; res++) {
		i = node[i][lr[res % lr_max]];
	}
	printf("%llu\n", res);
	return 0;
}
