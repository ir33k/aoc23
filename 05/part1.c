#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZ 7
#define MAP_VMAX 64

typedef unsigned map_id_t;

struct map {
	struct {
		map_id_t dst, src, len;
	} v[MAP_VMAX];
	int siz;
};

static map_id_t parse_unsigned(char *str)
{
	map_id_t num = 0;
	while (*str >= '0' && *str <= '9') {
		num = 10*num + (0x0F & *(str++));
	}
	return num;
}

static void map_parse(struct map *map)
{
	char buf[BUFSIZ], *bp;
	fgets(buf, sizeof(buf), stdin);
	while ((bp = fgets(buf, sizeof(buf), stdin))) {
		if (buf[0] == '\n') {
			break;
		}
		map->v[map->siz].dst = parse_unsigned(  bp); bp = strchr(bp, ' ');
		map->v[map->siz].src = parse_unsigned(++bp); bp = strchr(bp, ' ');
		map->v[map->siz].len = parse_unsigned(++bp);
		map->siz++;
	}
}

static map_id_t map_get(struct map *map, map_id_t id)
{
	int i;
	for (i = 0; i < map->siz; i++) {
		if (id < map->v[i].src || id >= map->v[i].src + map->v[i].len) {
			continue;
		}
		return  map->v[i].dst + (id - map->v[i].src);
	}
	return id;
}


int main(void)
{
	struct map map[MAP_SIZ] = {0};
	map_id_t id, seeds[32];
	map_id_t location = -1; /* Force integer overflow to init with biggest value. */
	int m, i, seeds_siz;
	char buf[BUFSIZ], *bp;
	bp = fgets(buf, sizeof(buf), stdin);
	for (seeds_siz = 0; (bp = strchr(bp, ' ')); seeds_siz++) {
		seeds[seeds_siz] = parse_unsigned(++bp);
	}
	fgets(buf, sizeof(buf), stdin);
	for (m = 0; m < MAP_SIZ; m++) {
		map_parse(&map[m]);
	}
	for (i = 0; i < seeds_siz; i++) {
		for (id = seeds[i], m = 0; m < MAP_SIZ; m++) {
			id = map_get(&map[m], id);
		}
		if (id < location) {
			location = id;
		}
	}
	printf("%u\n", location);
	return 0;
}
