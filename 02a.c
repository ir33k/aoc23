#include <stdio.h>
#include <stdlib.h>

#define MAX_RED   12
#define MAX_GREEN 13
#define MAX_BLUE  14

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
	int i = 0, skip, id, value, sum = 0;
	enum token token;
	char buf[BUFSIZ];
	while (fgets(buf, sizeof(buf), stdin)) {
		/* printf("%s", buf); */
		i = 0;
		while ((skip = get_token(buf + i, &token, &value))) {
			switch (token) {
			case T_NUL:
				break;
			case T_GAME:
				id = value;
				break;
			case T_RED:
				if (value > MAX_RED) {
					goto skip;
				}
				break;
			case T_GREEN:
				if (value > MAX_GREEN) {
					goto skip;
				}
				break;
			case T_BLUE:
				if (value > MAX_BLUE) {
					goto skip;
				}
				break;
			}
			i += skip;
		}
		sum += id;
	skip:
		continue;
	}
	printf("%d\n", sum);
	return 0;
}
