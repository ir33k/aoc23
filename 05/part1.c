#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAPSIZ 7

typedef unsigned long map_id_t;

struct map {
	map_id_t src, dst, len;
	struct map *next;       /* Linked list FTW!!! (^-^ ) */
};

static map_id_t parse_unsigned(char *str)
{
	map_id_t num = 0;
	while (*str >= '0' && *str <= '9') {
		num = 10*num + (0x0F & *(str++));
	}
	return num;
}

static struct map *map_parse(void)
{
	struct map *head = 0;
	struct map *node = 0;
	char buf[BUFSIZ], *bp;
	fgets(buf, sizeof(buf), stdin);
	node = head = malloc(sizeof(struct map));
	while ((bp = fgets(buf, sizeof(buf), stdin))) {
		if (buf[0] == '\n') {
			break;
		}
		node = node->next = malloc(sizeof(struct map));
		node->dst = parse_unsigned(  bp); bp = strchr(bp, ' ');
		node->src = parse_unsigned(++bp); bp = strchr(bp, ' ');
		node->len = parse_unsigned(++bp);
	}
	return head;
}

static map_id_t map_get(struct map *map, map_id_t id)
{
	struct map *node;
	for (node = map->next; node; node = node->next) {
		if (id < node->src || id >= node->src + node->len) {
			continue;
		}
		return node->dst + (id - node->src);
	}
	return id;
}


int main(void)
{
	struct map *map[MAPSIZ];
	map_id_t id, seeds[32];
	map_id_t location = -1; /* Force integer overflow to init with biggest value. */
	int m, i, seeds_siz;
	char buf[BUFSIZ], *bp;
	bp = fgets(buf, sizeof(buf), stdin);
	for (seeds_siz = 0; (bp = strchr(bp, ' ')); seeds_siz++) {
		seeds[seeds_siz] = parse_unsigned(++bp);
	}
	fgets(buf, sizeof(buf), stdin);
	for (m = 0; m < MAPSIZ; m++) {
		map[m] = map_parse();
	}
	for (i = 0; i < seeds_siz; i++) {
		for (id = seeds[i], m = 0; m < MAPSIZ; m++) {
			id = map_get(map[m], id);
		}
		if (id < location) {
			location = id;
		}
	}
	printf("%lu\n", location);
	return 0;
}
