#include "../walter.h"

TEST("Day 03 part 1")
{
	RUN("./part1.bin", "./example", S2F("4361\n"), 0, 0);
	RUN("./part1.bin", "./input", S2F("536576\n"), 0, 0);
}

TEST("Day 03 part 2")
{
	RUN("./part2.bin", "./example", S2F("467835\n"), 0, 0);
	RUN("./part2.bin", "./input", S2F("75741499\n"), 0, 0);
}
