#include "../walter.h"

TEST("Day 07 part 1")
{
	RUN("./part1.bin", "./example", S2F("6440\n"), 0, 0);
	RUN("./part1.bin", "./input", S2F("248836197\n"), 0, 0);
}

TEST("Day 07 part 2")
{
	RUN("./part2.bin", "./example", S2F("5905\n"), 0, 0);
	RUN("./part2.bin", "./input", S2F("251195607\n"), 0, 0);
}
