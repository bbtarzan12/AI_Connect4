#ifndef H_PUREMCTSKERNEL
#define H_PUREMCTSKERNEL

#include <iostream>

#include <cuda.h>
#include <curand_kernel.h>
#include "cuda_runtime.h"
#include "curand_kernel.h"
#include "device_launch_parameters.h"
#include "Type.h"

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
