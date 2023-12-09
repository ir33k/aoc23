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
	unsigned i, j, beg_siz=0, end;
	short node[sizeof(key)][3] = {0};
	short lr[BUFSIZ], beg[32];
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
		if (buf[j + 2] == 'A') {
			beg[beg_siz++] = i;
		}
		node[i][END] = buf[j + 2] == 'Z';
		key[i++] = buf + j;
	}
	for (i = 0, j = 0; buf[j]; j += 17, i++) {
		node[i][LEFT]  = index_of(key, buf + j + 7);
		node[i][RIGHT] = index_of(key, buf + j + 12);
	}
	for (res = 0, end = 0; end != beg_siz; res++) {
		for (end = 0, j = 0; j < beg_siz; j++) {
			beg[j] = node[beg[j]][lr[res % lr_max]];
			end += node[beg[j]][END];
		}
	}
	printf("%llu\n", res);
	return 0;
}
