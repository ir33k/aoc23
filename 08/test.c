#include "../walter.h"

TEST("Day 08 part 1")
{
	RUN("./part1.bin", "./example", S2F("2\n"), 0, 0);
	RUN("./part1.bin", "./example2", S2F("6\n"), 0, 0);
	RUN("./part1.bin", "./input", S2F("15871\n"), 0, 0);
}

TEST("Day 08 part 2")
{
	RUN("./part2.bin", "./example3", S2F("6\n"), 0, 0);
}

SKIP("Day 08 part 2 final input skipped because it's very slow")
{
	RUN("./part2.bin", "./input", S2F("\n"), 0, 0);
}
