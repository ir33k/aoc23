#include "../walter.h"

TEST("Day 05 part 1")
{
	RUN("./part1.bin", "./example", S2F("35\n"), 0, 0);
	RUN("./part1.bin", "./input",   S2F("322500873\n"), 0, 0);
	RUN("./part1.bin", "./input2",  S2F("289863851\n"), 0, 0);
}

TEST("Day 05 part 2")
{
	RUN("./part2.bin", "./example", S2F("46\n"), 0, 0);
}

SKIP("Day 05 part 2 final input skipped because it's very slow")
{
	/* This takes couple of minutes to compute. */
	RUN("./part2.bin", "./input", S2F("108956227\n"), 0, 0);
}
