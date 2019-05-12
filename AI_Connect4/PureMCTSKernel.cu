#include "PureMCTSKernel.cuh"

#include "Player.h"
#include "Map.h"
#include "Random.h"

#include <iostream>
#include "CommandLineRenderer.h"

using namespace std;

__device__ uint32_t xor128()
{
	static uint32_t seed = 1;
	uint32_t t = 3906;
	seed ^= t << 15;
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

__device__ int Random(int min, int max)
{
	return PSEUDO_FLOOR(((double)xor128() / 0xffffffff) * (max - min + 1)) + min;
}

__host__ __device__ inline int Convert2Dto1D(const Column column, const Row row)
{
	return row * MAX_COLUMN + column;
}

__device__ GPUCoord GetEmptyCoord(ID* map, const Column column, bool& isValid)
{
	for (Row row = 0; row < MAX_ROW; row++)
	{
		if (map[Convert2Dto1D(column, row)] != EMPTY_ID)
			continue;

		isValid = true;
		return GPUCoord(column, row);
	}

	isValid = false;
	return GPUCoord();
}

__device__ inline bool IsColumnValid(ID* map, const Column column)
{
	return map[Convert2Dto1D(column, MAX_ROW - 1)] == EMPTY_ID;
}

__device__ bool IsMapFull(ID* map)
{
	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		if (map[Convert2Dto1D(column, MAX_ROW - 1)] == EMPTY_ID)
			return false;
	}
	return true;
}

__device__ inline bool CheckCoordIsInBound(const Column column, const Row row)
{
	//if (column >= MAX_COLUMN || column < 0)
	//	return false;

	//if (row >= MAX_ROW || row < 0)
	//	return false;

	//return true;

	return !((column >= MAX_COLUMN || column < 0) || ((row >= MAX_ROW || row < 0)));
}

__device__ int GetNumOfNeighbor(ID* map, const GPUCoord originCoord, const int deltaColumn, const int deltaRow, const ID id)
{
	GPUCoord neighborCoord;
	neighborCoord.column = originCoord.column + deltaColumn;
	neighborCoord.row = originCoord.row + deltaRow;

	if (!CheckCoordIsInBound(neighborCoord.column, neighborCoord.row))
		return 0;

	if (map[Convert2Dto1D(neighborCoord.column, neighborCoord.row)] == id)
		return GetNumOfNeighbor(map, neighborCoord, deltaColumn, deltaRow, id) + 1;

	return 0;
}

__device__ void GetNumOfNeighbors(ID* map, const GPUCoord coord, const ID id, int* neighbors, bool selfContained = true)
{
	const Column& column = coord.column;
	const Row& row = coord.row;

	int index = 0;
	for (int neighborColumn = column - 1; neighborColumn <= column + 1; neighborColumn++)
	{
		for (int neighborRow = row - 1; neighborRow <= row; neighborRow++)
		{
			if (neighborColumn == column && neighborRow == row)
				continue;

			if (neighborColumn == column + 1 && neighborRow == row)
				continue;

			int deltaColumn = neighborColumn - column;
			int deltaRow = neighborRow - row;
			int numOfNeighbor = GetNumOfNeighbor(map, coord, deltaColumn, deltaRow, id) + GetNumOfNeighbor(map, coord, -deltaColumn, -deltaRow, id) + (selfContained ? 1 : 0);
			neighbors[index++] = numOfNeighbor;
		}
	}
}
 
__device__ bool IsGameEnd(ID* map, const GPUCoord coord, const ID id)
{
	int numOfNeighbors[4] = { 0, 0, 0, 0 };
	GetNumOfNeighbors(map, coord, id, &numOfNeighbors[0]);

	int maxNeighbor = -1;
	for (int i = 0; i < 4; i++)
	{
		if(maxNeighbor > numOfNeighbors[i])
			continue;

		maxNeighbor = numOfNeighbors[i];

		if (maxNeighbor >= 4)
			return true;
	}
	return false;
}

__device__ void SetCoord(ID* map, const ID id, const GPUCoord coord, GPUCoord& lastMove)
{
	if (!CheckCoordIsInBound(coord.column, coord.row))
		return;
	lastMove = coord;
	map[Convert2Dto1D(coord.column, coord.row)] = id;
}

__global__ void SimulationKernel(ID* globalMap, const KernelData kernelData, int* numSimulation, int* totalWin)
{
	ID currentID = kernelData.id;
	ID winID = currentID;
	GPUCoord lastMove = kernelData.lastMove;

	ID map[MAX_COLUMN * MAX_ROW];

	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		for (Row row = 0; row < MAX_ROW; row++)
		{
			int index = Convert2Dto1D(column, row);
			map[index] = globalMap[index];
		}
	}

	while (true)
	{
		if (IsGameEnd(map, lastMove, currentID))
		{
			winID = currentID;
			break;
		}

		if (IsMapFull(map))
		{
			winID = EMPTY_ID;
			break;
		}

		currentID = currentID ^ 1;
		Column validColumns[MAX_COLUMN];
		int numOfValidColumns = 0;

		for (Column column = 0; column < MAX_COLUMN; column++)
		{
			if (!IsColumnValid(map, column))
				continue;

			validColumns[numOfValidColumns++] = column;
		}

		if (numOfValidColumns <= 0)
		{
			printf("Un Error Occured 1 %d\n", numOfValidColumns);
			return;
		}

		int randomIndex = Random(0, numOfValidColumns - 1);
		if (randomIndex >= numOfValidColumns)
		{
			printf("randomIndex >= numOfValidColumns\n");
			return;
		}

		Column randomColumn = validColumns[randomIndex];

		bool isValid = false;
		GPUCoord randomCoord = GetEmptyCoord(map, randomColumn, isValid);
		if (!isValid)
		{
			printf("Un Error Occured 2 randomColumn : %d \n", randomColumn);
			return;
		}

		SetCoord(map, currentID, randomCoord, lastMove);
	}

	if (winID == kernelData.id)
	{
		atomicAdd(totalWin, 1);
	}
	atomicAdd(numSimulation, 1);
}

void Simulation(Map& childMap, const ID id, int maxSimulation, int* numSimulation, int* totalWin)
{
	const int block = 1024;
	const int grid = ceil((float)maxSimulation / block);

	ID cpuMap[MAX_COLUMN * MAX_ROW];
	
	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		for (Row row = 0; row < MAX_ROW; row++)
		{
			cpuMap[Convert2Dto1D(column, row)] = childMap[column][row];
		}
	}

	int *gpuNumSimuation, *gpuTotalWin;
	gpuErrorCheck(cudaMalloc(&gpuNumSimuation, sizeof(int)));
	gpuErrorCheck(cudaMalloc(&gpuTotalWin, sizeof(int)));
	gpuErrorCheck(cudaMemcpy(gpuNumSimuation, numSimulation, sizeof(int), cudaMemcpyHostToDevice));
	gpuErrorCheck(cudaMemcpy(gpuTotalWin, totalWin, sizeof(int), cudaMemcpyHostToDevice));

	ID *gpuMap;
	gpuErrorCheck(cudaMalloc(&gpuMap, sizeof(ID) * MAX_COLUMN * MAX_ROW));
	gpuErrorCheck(cudaMemcpy(gpuMap, cpuMap, sizeof(ID) * MAX_COLUMN * MAX_ROW, cudaMemcpyHostToDevice));

	KernelData kernelData;
	kernelData.id = id;
	kernelData.lastMove.column = childMap.lastMove.first;
	kernelData.lastMove.row = childMap.lastMove.second;

	SimulationKernel << <grid, block >> > (gpuMap, kernelData, gpuNumSimuation, gpuTotalWin);
	gpuErrorCheck(cudaDeviceSynchronize());

	gpuErrorCheck(cudaMemcpy(numSimulation, gpuNumSimuation, sizeof(int), cudaMemcpyDeviceToHost));
	gpuErrorCheck(cudaMemcpy(totalWin, gpuTotalWin, sizeof(int), cudaMemcpyDeviceToHost));
}
