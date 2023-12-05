#include "../walter.h"

TEST("Day 02 part 1")
{
	RUN("./part1.bin", "./example", S2F("8\n"), 0, 0);
	RUN("./part1.bin", "./input", S2F("2317\n"), 0, 0);
}

TEST("Day 02 part 2")
{
	RUN("./part2.bin", "./example", S2F("2286\n"), 0, 0);
	RUN("./part2.bin", "./input", S2F("74804\n"), 0, 0);
}
