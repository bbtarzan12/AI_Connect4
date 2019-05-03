#ifndef H_RANDOM
#define H_RANDOM

#include <stdint.h>

template<typename T>
class RandomGenerator
{
public:

#define PSEUDO_FLOOR( V ) ((V) >= 0 ? (int)(V) : (int)((V) - 1))

	// [min, max] Uniform Random
	static int Random(int min, int max)
	{
		return PSEUDO_FLOOR((T::Random()) * (max - min + 1)) + min;
	}
};

class XOR128
{
public:
	static float Random();

private:
	static uint32_t xor128();
	static uint32_t seed;
};

#endif
