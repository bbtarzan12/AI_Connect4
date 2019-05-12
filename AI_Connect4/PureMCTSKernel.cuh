#ifndef H_PUREMCTSKERNEL
#define H_PUREMCTSKERNEL

#include <iostream>

#include <cuda.h>
#include <curand_kernel.h>
#include "cuda_runtime.h"
#include "curand_kernel.h"
#include "device_launch_parameters.h"
#include "Type.h"

#define gpuErrorCheck(ans) { gpuAssert((ans), __FILE__, __LINE__); }
#define PSEUDO_FLOOR( V ) ((V) >= 0 ? (int)(V) : (int)((V) - 1))

inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort)
		{
			system("pause");
			exit(code);
		}
	}
}


class Map;

struct GPUCoord
{
	__device__ GPUCoord(Column column = 0, Row row = 0)
		:column(column), row(row)
	{

	}
	Column column;
	Row row;
};

struct KernelData
{
	GPUCoord lastMove;
	ID id;
};

void Simulation(Map& childMap, const ID id, int maxSimulation, int* numSimulation, int* totalWin);

#endif
