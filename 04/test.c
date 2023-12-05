#include "../walter.h"

TEST("Day 04 part 1")
{
	RUN("./part1.bin", "./example", S2F("13\n"), 0, 0);
	RUN("./part1.bin", "./input", S2F("24848\n"), 0, 0);
}

TEST("Day 04 part 2")
{
	RUN("./part2.bin", "./example", S2F("30\n"), 0, 0);
	RUN("./part2.bin", "./input", S2F("7258152\n"), 0, 0);
}
