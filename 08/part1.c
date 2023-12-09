#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZ (16 * 1024)

struct node {
	char *key;
	int child[2];           /* [left, right] */
};

static int index_of(struct node *node, char *find)
{
	int i;
	for (i = 0; node[i].key; i++) {
		if (!strcmp(node[i].key, find)) {
			return i;
		}
	}
	return -1;
}

int main(void)
{
	char buf[BSIZ], lr[BUFSIZ];
	struct node node[1024] = {0};
	int i,j, b, len, lr_max, beg, end;
	fgets(lr, sizeof(lr), stdin);
	lr_max = strlen(lr) - 1;
	for (i = 0; i < lr_max; i++) {
		lr[i] = lr[i] == 'R';
	}
	fgets(buf, sizeof(buf), stdin);
	while ((i = fread(buf, 1, sizeof(buf), stdin))) len += i;
	buf[len] = 0;
	for (i = 0, b = 0; buf[b]; b += 17) {
		buf[b +  3] = 0;
		buf[b + 10] = 0;
		buf[b + 15] = 0;
		if (!strcmp(buf + b, "AAA")) {
			beg = i;
		}
		if (!strcmp(buf + b, "ZZZ")) {
			end = i;
		}
		node[i++].key = buf + b;
	}
	for (i = 0, b = 0; buf[b]; b += 17, i++) {
		node[i].child[0] = index_of(node, buf + b + 7);
		node[i].child[1] = index_of(node, buf + b + 12);
	}
	i = beg;
	for (j = 0; i != end; j++) {
		i = node[i].child[(int)lr[j % lr_max]];
	}
	printf("%d\n", j);
	return 0;
}
