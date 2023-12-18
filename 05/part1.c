#include <stdio.h>
#include <string.h>

#define MAP_MAX 256
#define MAP_COUNT 7

typedef unsigned map_id_t;

struct map {
	map_id_t dst, src, len;
};

static map_id_t parse_unsigned(char *str)
{
	map_id_t num = 0;
	while (*str >= '0' && *str <= '9') {
		num = 10*num + (0x0F & *(str++));
	}
	return num;
}

static int map_parse(struct map *map, int i)
{
	char buf[BUFSIZ], *bp;
	fgets(buf, sizeof(buf), stdin);
	while ((bp = fgets(buf, sizeof(buf), stdin))) {
		if (buf[0] == '\n') {
			break;
		}
		map[i].dst = parse_unsigned(  bp); bp = strchr(bp, ' ');
		map[i].src = parse_unsigned(++bp); bp = strchr(bp, ' ');
		map[i].len = parse_unsigned(++bp);
		i++;
	}
	return i;
}

static map_id_t map_get(struct map *map, int i, int siz, map_id_t id)
{
	for (; i < siz; i++) {
		if (id >= map[i].src && id < map[i].src + map[i].len) {
			return  map[i].dst + (id - map[i].src);
		}
	}
	return id;
}


int main(void)
{
	struct map map[MAP_MAX];
	int mapi[MAP_COUNT+1] = {0};
	map_id_t id, seeds[32];
	map_id_t location = -1; /* Force integer overflow to init with biggest value. */
	int m, i, seeds_siz;
	char buf[BUFSIZ], *bp;
	bp = fgets(buf, sizeof(buf), stdin);
	for (seeds_siz = 0; (bp = strchr(bp, ' ')); seeds_siz++) {
		seeds[seeds_siz] = parse_unsigned(++bp);
	}
	fgets(buf, sizeof(buf), stdin);
	for (m = 0; m < MAP_COUNT; m++) {
		mapi[m+1] = map_parse(map, mapi[m]);
	}
	for (i = 0; i < seeds_siz; i++) {
		for (id = seeds[i], m = 0; m < MAP_COUNT; m++) {
			id = map_get(map, mapi[m], mapi[m+1], id);
		}
		if (id < location) {
			location = id;
		}
	}
	printf("%u\n", location);
	return 0;
}
