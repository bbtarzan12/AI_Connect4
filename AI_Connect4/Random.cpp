#include "Random.h"
#include <time.h>


uint32_t XOR128::seed = 1;

double XOR128::Random()
{
	return (double) xor128() / (0xffffffff);
}

uint32_t XOR128::xor128()
{
	static uint32_t t = time(nullptr);
	seed ^= t << 15;
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
