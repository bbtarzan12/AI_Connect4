#include "Random.h"
#include <time.h>


uint32_t XOR128::seed = 1;

float XOR128::Random()
{
	return (float) xor128() / 0xffffffff; // 0xffffffff
}

uint32_t XOR128::xor128()
{
	uint32_t t = time(nullptr);
	seed ^= t << 15;
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
