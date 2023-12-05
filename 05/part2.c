#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long id_t;

struct seed {
	id_t beg, end;
};

struct map {
	id_t src, dst, len;
	struct map *next;       /* Linked list FTW!!! (^-^ ) */
};

static struct map *map_parse(void)
{
	struct map *head = 0;
	struct map *node = 0;
	char buf[BUFSIZ], *bp;
	fgets(buf, sizeof(buf), stdin);
	while ((bp = fgets(buf, sizeof(buf), stdin))) {
		if (buf[0] == '\n') {
			break;
		}
		if (node) {
			node->next = malloc(sizeof(struct map));
			node = node->next;
		} else {
			node = malloc(sizeof(struct map));
			head = node;
		}
		node->dst = atoi(bp);
		bp = strchr(bp, ' ');
		node->src = atoi(++bp);
		bp = strchr(bp, ' ');
		node->len = atoi(++bp);
	}
	return head;
}

static id_t map_get(struct map *map, id_t id)
{
	struct map *node;
	for (node = map; node; node = node->next) {
		if (id < node->src || id >= node->src + node->len) {
			continue;
		}
		return node->dst + (id - node->src);
	}
	return id;
}


int main(void)
{
	struct map *seed_soil;
	struct map *soil_fertilizer;
	struct map *fertilizer_water;
	struct map *water_light;
	struct map *light_temperature;
	struct map *temperature_humidity;
	struct map *humidity_location;
	struct seed seeds[16];
	id_t id, beg;
	id_t location = -1; /* Force integer overflow to init with biggest value. */
	id_t i, seeds_siz = 0;
	char buf[BUFSIZ], *bp;
	/* seeds */
	bp = fgets(buf, sizeof(buf), stdin);
	while ((bp = strchr(bp, ' '))) {
		seeds[seeds_siz].beg = atoi(++bp);
		bp = strchr(bp, ' ');
		seeds[seeds_siz].end = atoi(++bp) + seeds[seeds_siz].beg;
		seeds_siz++;
	}
	fgets(buf, sizeof(buf), stdin);
	seed_soil            = map_parse();
	soil_fertilizer      = map_parse();
	fertilizer_water     = map_parse();
	water_light          = map_parse();
	light_temperature    = map_parse();
	temperature_humidity = map_parse();
	humidity_location    = map_parse();
	for (i = 0; i < seeds_siz; i++) {
		for (beg = seeds[i].beg; beg < seeds[i].end; beg++) {
			id = map_get(seed_soil, beg);
			id = map_get(soil_fertilizer, id);
			id = map_get(fertilizer_water, id);
			id = map_get(water_light, id);
			id = map_get(light_temperature, id);
			id = map_get(temperature_humidity, id);
			id = map_get(humidity_location, id);
			if (id < location) {
				location = id;
			}
		}
	}
	printf("%llu\n", location);
	return 0;
}
