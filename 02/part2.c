#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum token {
	T_GAME  = 'G',          /* Beginning of the game, value is game ID */
	T_RED   = 'r',          /* Red cubes, value is number of cubes */
	T_GREEN = 'g',          /* Green cubes, value is number of cubes */
	T_BLUE  = 'b',          /* Blue cubes, value is number of cubes */
	T_NEXT  = ',',          /* We expect to grab more cubes, no value */
	T_SET   = ';',          /* End of the game set, value unchanged  */
	T_END   = '\n',         /* End of the game, no value */
};

/* How many bytes to skip in order to get to next token. */
static int s_skip[] = {
	[T_GAME]  = 2,
	[T_RED]   = 3,
	[T_GREEN] = 5,
	[T_BLUE]  = 4,
	[T_SET]   = 2,
	[T_NEXT]  = 2,
	[T_END]   = 0,
};

/* Check what is the current TOKEN in STR string.  Set TOKEN VALUE.
 * Return number of bytes to advance in STR. */
static int get_token(char *str, enum token *token, int *value)
{
	int i = 0;
	switch (str[0]) {
	case T_GAME:
		i = 5;
		*value = atoi(str + i);
		while (str[++i] != ':');
		/* fallthrough */
	case T_SET:
	case T_NEXT:
	case T_END:
		*token = str[0];
		return i + s_skip[*token];
	}
	*value = atoi(str + i);
	while (str[i++] != ' ');
	*token = str[i];
	i += s_skip[*token];
	return i;
}

int main(void)
{
	int i = 0, v, sum = 0;
	enum token t;
	char buf[BUFSIZ];
	int min[] = {
		[T_RED]   = 0,
		[T_GREEN] = 0,
		[T_BLUE]  = 0,
	};
	while (fgets(buf, sizeof(buf), stdin)) {
		for (i = 0; i += get_token(buf + i, &t, &v);) {
			switch ((int)t) {
			case T_RED:
			case T_GREEN:
			case T_BLUE:
				min[t] = min[t] > v ? min[t] : v;
				break;
			case T_END:
				goto end;
			}
		}
	end:
		sum += min[T_RED] * min[T_GREEN] * min[T_BLUE];
		memset(min, 0, sizeof(min));
	}
	printf("%d\n", sum);
	return 0;
}
