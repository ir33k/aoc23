#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct race {
	int time, distance;
	struct race *next;
};

int main(void)
{
	char buf[BUFSIZ], *bp;
	struct race *race = 0, *node;
	int i, travel, win, res = 1;
	bp = fgets(buf, sizeof(buf), stdin);
	while ((bp = strchr(bp, ' '))) {
		if (race) {
			node->next = malloc(sizeof(struct race));
			node = node->next;
		} else {
			race = malloc(sizeof(struct race));
			node = race;
		}
		while (*bp == ' ') bp++;
		memset(node, 0, sizeof(*node));
		node->time = atoi(bp);
	}
	bp = fgets(buf, sizeof(buf), stdin);
	for (node = race; (bp = strchr(bp, ' ')); node = node->next) {
		while (*bp == ' ') bp++;
		node->distance = atoi(bp);
	}
	for (node = race; node; node = node->next) {
		win = 0;
		for (i = 1; i < node->time; i++) {
			travel = (node->time - i) * i;
			if (travel > node->distance) {
				win++;
			}
		}
		res *= win;
	}
	printf("%d\n", res);
	return 0;
}
