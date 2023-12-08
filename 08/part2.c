#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MHM_IMPLEMENTATION
#include "../mhm.h"

#define BSIZ (16 * 1024)

struct node {
	char *key[2];
};

int main(void)
{
	char buf[BSIZ], lr[BUFSIZ], *key[16];
	struct node *node;
	int k, lr_len, ki, end;
	long long unsigned i;
	size_t len;
	Mhm hm;
	mhm_init(&hm, 2048, mhm_hash_djb2);
	fgets(lr, sizeof(lr), stdin);
	lr_len = strlen(lr) - 1;
	fgets(buf, sizeof(buf), stdin);
	while ((i = fread(buf, 1, sizeof(buf), stdin))) len += i;
	buf[len] = 0;
	for (i = 0, ki = 0; buf[i]; i += 17) {
		node = malloc(sizeof(node));
		buf[i +  3] = 0;
		buf[i + 10] = 0;
		buf[i + 15] = 0;
		if (buf[i + 2] == 'A') key[ki++] = buf + i;
		node->key[0] = buf + i + 7;  /* Left */
		node->key[1] = buf + i + 12; /* Right */
		mhm_set(&hm, buf + i, node);
	}
	for (i = 0, end = 0; !end; i++) {
		end = 1;
		for (k = 0; k < ki; k++) {
			node = mhm_get(&hm, key[k]);
			key[k] = node->key[lr[i % lr_len] == 'R'];
			if (key[k][2] != 'Z') end = 0;
		}
	}
	printf("%llu\n", i);
	return 0;
}
