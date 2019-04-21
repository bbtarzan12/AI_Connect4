#ifndef H_RANDOM
#define H_RANDOM

#include <stdint.h>

template<typename T>
class RandomGenerator
{
public:

	// [min, max] Uniform Random
	static float Random(float min, float max)
	{
		return floor(T::Random() * (max - min + 1)) + min;
	}

	// [min, max] Uniform Random
	static int Random(int min, int max)
	{
		return floor(T::Random() * (max - min + 1)) + min;
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
