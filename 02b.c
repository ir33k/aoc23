#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

/* T_NUL means end of the game set. */
enum token { T_NUL = 0, T_GAME, T_RED, T_GREEN, T_BLUE };

static size_t get_token(char *str, enum token *token, int *value)
{
	size_t i = 0;
	switch (str[0]) {
	case '\n':
		return 0;
	case ';':
		*token = T_NUL;
		return 2;
	case 'G':
		*token = T_GAME;
		i = 5;
		*value = atoi(str + i);
		while (str[i++] != ':');
		return i + 1;
	case ',':
		i += 2;
		break;
	}
	*value = atoi(str + i);
	while (str[i++] != ' ');
	switch (str[i]) {
	case 'r': *token = T_RED;   break;
	case 'g': *token = T_GREEN; break;
	case 'b': *token = T_BLUE;  break;
	}
	while (str[i] != ',' &&
	       str[i] != ';' &&
	       str[i] != '\n') i++;
	return i;
}

int main(void)
{
	int i = 0, skip, value, sum = 0;
	int minr = 0, ming = 0, minb = 0;
	enum token token;
	char buf[BUFSIZ];
	while (fgets(buf, sizeof(buf), stdin)) {
		/* printf("%s", buf); */
		i = 0;
		while ((skip = get_token(buf + i, &token, &value))) {
			switch (token) {
			case T_NUL:
			case T_GAME:
				break;
			case T_RED:
				minr = MAX(minr, value);
				break;
			case T_GREEN:
				ming = MAX(ming, value);
				break;
			case T_BLUE:
				minb = MAX(minb, value);
				break;
			}
			i += skip;
		}
		sum += minr * ming * minb;
		minr = 0;
		ming = 0;
		minb = 0;
	}
	printf("%d\n", sum);
	return 0;
}
