#include "../walter.h"

TEST("Day 01 part 1")
{
	RUN("./part1.bin", "./example", S2F("142\n"), 0, 0);
	RUN("./part1.bin", "./input", S2F("54630\n"), 0, 0);
}

TEST("Day 01 part 2")
{
	RUN("./part2.bin", "./example2", S2F("281\n"), 0, 0);
	RUN("./part2.bin", "./input", S2F("54770\n"), 0, 0);
}
