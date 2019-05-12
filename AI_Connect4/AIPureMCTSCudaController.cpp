#include "AIPureMCTSCudaController.h"

#include <algorithm>
#include <iostream>
#include <chrono>

#include "PureMCTSKernel.cuh"
#include "Player.h"
#include "Random.h"
#include "CommandLineRenderer.h"


using namespace std;
using namespace std::chrono;

AIPureMCTSCudaController::AIPureMCTSCudaController(const std::shared_ptr<Player>& player)
{
	this->player = player;

	cudaDeviceProp deviceProp;
	gpuErrorCheck(cudaGetDeviceProperties(&deviceProp, 0));
	
	printf("GPU Device 이름 : %s\n", deviceProp.name);
	printf("Cuda Compatibility 버전 : %d.%d\n", deviceProp.major, deviceProp.minor);
	printf("본 프로젝트는 Cuda 10.1, GTX 1060 3GB, 6.1의 Compatibility 버전을 기준으로 작성되었습니다.\n");
}

Column AIPureMCTSCudaController::GetPlayerInput()
{
	auto start = high_resolution_clock::now();

	const ID id = player->GetPlayerID();
	Map& map = player->GetGameMap();
	const int maxSimulation = 100000000;

	Column maxColumn = 0;
	float maxWinningRate = -1;
	int numSimulations = 0;
	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		bool isvalid = false;
		Coord coord = map.GetEmptyCoord(column, isvalid);
		if (!isvalid)
		{
			continue;
		}


		Map childMap = map;
		childMap.SetCoord(id, coord);

		int totalWin = 0;
		int numSimulation = 0;

		Simulation(childMap, id, maxSimulation, &numSimulation, &totalWin);

		numSimulations += numSimulation;
		float winningRate = (float)totalWin / numSimulation;

		if (winningRate > maxWinningRate)
		{
			maxColumn = column;
			maxWinningRate = winningRate;
		}

		cout << "numSimulation : " << numSimulation << " totalWin : " << totalWin << " Winning Rate : " << winningRate << endl;
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << duration.count() / 1000.0f << "초 걸렸습니다 (초당 " << (int)(numSimulations / (duration.count() / 1000.0f)) << " 시뮬레이션)" << endl;
	cout << "시뮬레이션들 중 가장 높은 승률을 가진 자식을 선택한다." << endl;

	return maxColumn;
}