#include "../walter.h"

TEST("Day 06 part 1")
{
	RUN("./part1.bin", "./example", S2F("288\n"), 0, 0);
	RUN("./part1.bin", "./input", S2F("512295\n"), 0, 0);
}

TEST("Day 06 part 2")
{
	RUN("./part2.bin", "./example", S2F("71503\n"), 0, 0);
	RUN("./part2.bin", "./input", S2F("36530883\n"), 0, 0);
}
