#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZ (16 * 1024)

struct node {
	char key[4];
	int child[2];           /* [left, right] */
};

static int index_of(struct node *node, char *find)
{
	int i;
	for (i = 0; node[i].key[0]; i++) {
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
	int i,j, b, len, lr_max, key[1024], key_count=0, end;
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
		if (buf[b + 2] == 'A') {
			key[key_count++] = i;
		}
		strcpy(node[i++].key, buf + b);
	}
	for (i = 0, b = 0; buf[b]; b += 17, i++) {
		node[i].child[0] = index_of(node, buf + b + 7);
		node[i].child[1] = index_of(node, buf + b + 12);
	}
	for (j = 0, end = 0; !end; j++) {
		end = 1;
		for (i = 0; i < key_count; i++) {
			key[i] = node[key[i]].child[(int)lr[j % lr_max]];
			if (node[key[i]].key[2] != 'Z') {
				end = 0;
			}
		}
	}
	printf("%d\n", j);
	return 0;
}
