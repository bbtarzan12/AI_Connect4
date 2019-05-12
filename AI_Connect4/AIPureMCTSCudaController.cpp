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

	return maxColumn;
}