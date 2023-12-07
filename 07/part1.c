#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hand {
	char cards[5];
	int bid;
};

static int card_index(char card)
{
	switch (card) {
	case '2': return 0;
	case '3': return 1;
	case '4': return 2;
	case '5': return 3;
	case '6': return 4;
	case '7': return 5;
	case '8': return 6;
	case '9': return 7;
	case 'T': return 8;
	case 'J': return 9;
	case 'Q': return 10;
	case 'K': return 11;
	case 'A': return 12;
	};
	assert(0 && "Unreachable");
	return 0;
}

static int cards_strength(char cards[5])
{
	char count[13] = {0};
	int i=5, threes=0, twos=0;
	while (i--) {
		count[card_index(cards[i])]++;
	}
	for (i = 0; i < 13; i++) {
		switch (count[i]) {
		case 5: return 6;
		case 4: return 5;
		case 3: threes++; break;
		case 2: twos++;   break;
		}
	}
	if (threes &&  twos) return 4;
	if (threes && !twos) return 3;
	if (twos == 2)       return 2;
	if (twos == 1)       return 1;
	return 0;
}

static int hands_sort(const void *in_a, const void *in_b)
{
	struct hand *a = (struct hand*)in_a;
	struct hand *b = (struct hand*)in_b;
	int a_strength = cards_strength(a->cards);
	int b_strength = cards_strength(b->cards);
	int i;
	if (a_strength != b_strength) return a_strength - b_strength;
	for (i = 0; i < 5; i++) {
		if (card_index(a->cards[i]) == card_index(b->cards[i])) {
			continue;
		}
		return card_index(a->cards[i]) - card_index(b->cards[i]);
	}
	return 0;
}

int main(void)
{
	char buf[BUFSIZ], *bp;
	struct hand hands[1024];
	size_t i, hands_siz;
	long unsigned win = 0;
	for (i = 0; (bp = fgets(buf, sizeof(buf), stdin)); i++) {
		sscanf(bp, "%s %d\n", hands[i].cards, &hands[i].bid);
	}
	hands_siz = i;
	qsort(hands, hands_siz, sizeof(hands[0]), hands_sort);
	for (i = 0; i < hands_siz; i++) {
		win += (i+1) * hands[i].bid;
	}
	printf("%lu\n", win);
	return 0;
}
