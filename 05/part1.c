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
	int i, seeds_siz;
	char buf[BUFSIZ], *bp;
	bp = fgets(buf, sizeof(buf), stdin);
	for (seeds_siz = 0; (bp = strchr(bp, ' ')); seeds_siz++) {
		seeds[seeds_siz] = parse_unsigned(++bp);
	}
	fgets(buf, sizeof(buf), stdin);
	mapi[1] = map_parse(map, mapi[0]);
	mapi[2] = map_parse(map, mapi[1]);
	mapi[3] = map_parse(map, mapi[2]);
	mapi[4] = map_parse(map, mapi[3]);
	mapi[5] = map_parse(map, mapi[4]);
	mapi[6] = map_parse(map, mapi[5]);
	mapi[7] = map_parse(map, mapi[6]);
	for (i = 0; i < seeds_siz; i++) {
		id = seeds[i];
		id = map_get(map, mapi[0], mapi[1], id);
		id = map_get(map, mapi[1], mapi[2], id);
		id = map_get(map, mapi[2], mapi[3], id);
		id = map_get(map, mapi[3], mapi[4], id);
		id = map_get(map, mapi[4], mapi[5], id);
		id = map_get(map, mapi[5], mapi[6], id);
		id = map_get(map, mapi[6], mapi[7], id);
		if (id < location) {
			location = id;
		}
	}
	printf("%u\n", location);
	return 0;
}
