#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define MAP_MAX 256
#define MAP_COUNT 7

struct seed {
	unsigned beg, end;
};

struct map {
	unsigned dst, src, max;
};

static unsigned parse_unsigned(char *str)
{
	unsigned num = 0;
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
		map[i].max = parse_unsigned(++bp) + map[i].src;
		i++;
	}
	return i;
}

static unsigned map_get(struct map *map, int beg, int end, unsigned id)
{
	int i, step = (end - beg) / 2;
	for (i = beg + step; step && id < map[i].src;) {
		i = beg + (step /= 2);
	}
	for (; i < end; i++) {
		if (id < map[i].src) {
			break;
		}
		if (id < map[i].max) {
			return  map[i].dst + (id - map[i].src);
		}
	}
	return id;
}

static int map_qsort(struct map *a, struct map *b)
{
	long int res = ((long int)a->src) - ((long int)b->src);
	if (res < 0) return -1;
	if (res > 0) return  1;
	return 0;
}

int main(void)
{
	struct map map[MAP_MAX];
	struct seed seeds[16];
	unsigned id, beg;
	unsigned res = -1, *location; /* Force integer overflow to init with biggest value. */
	int i, seeds_siz = 0, mapi[MAP_COUNT+1] = {0}, shmid;
	pid_t pid[16];
	char buf[BUFSIZ], *bp;
	if ((shmid = shmget(0, sizeof(unsigned) * 16, 0666 | IPC_CREAT)) == -1) {
		err(1, "shmget");
	}
	if ((location = shmat(shmid, 0, 0)) == (void *)-1) {
		err(1, "shmat");
	}
	memset(location, (unsigned)-1, sizeof(unsigned) * 16);
	bp = fgets(buf, sizeof(buf), stdin);
	while ((bp = strchr(bp, ' '))) {
		seeds[seeds_siz].beg = parse_unsigned(++bp);
		bp = strchr(bp, ' ');
		seeds[seeds_siz].end = parse_unsigned(++bp) + seeds[seeds_siz].beg;
		seeds_siz++;
	}
	fgets(buf, sizeof(buf), stdin);
	for (i = 0; i < MAP_COUNT; i++) {
		mapi[i+1] = map_parse(map, mapi[i]);
	}
	for (i = 0; i < MAP_COUNT; i++) {
		qsort(map + mapi[i], mapi[i+1] - mapi[i], sizeof(map[0]),
		      (int (*)(const void *, const void *))map_qsort);
	}
	for (i = 0; i < seeds_siz; i++) {
		if ((pid[i] = fork()) == -1) {
			err(1, "fork");
		}
		if (pid[i]) {   /* Parent */
			continue;
		}
		/* Child */
		for (beg = seeds[i].beg; beg < seeds[i].end; beg++) {
			id = map_get(map, mapi[0], mapi[1], beg);
			id = map_get(map, mapi[1], mapi[2], id);
			id = map_get(map, mapi[2], mapi[3], id);
			id = map_get(map, mapi[3], mapi[4], id);
			id = map_get(map, mapi[4], mapi[5], id);
			id = map_get(map, mapi[5], mapi[6], id);
			id = map_get(map, mapi[6], mapi[7], id);
			if (id < location[i]) {
				location[i] = id;
			}
		}
		return 0;
	}
	for (i = 0; i < seeds_siz; i++) {
		if (waitpid(pid[i], 0, 0) == -1) {
			err(1, "waitpid %d", i);
		}
		if (location[i] < res) {
			res = location[i];
		}
	}
	printf("%u\n", res);
	return 0;
}
