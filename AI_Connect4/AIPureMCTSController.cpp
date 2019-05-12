#include "AIPureMCTSController.h"
#include <algorithm>
#include <iostream>
#include "Player.h"
#include "Random.h"
#include "CommandLineRenderer.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

AIPureMCTSController::AIPureMCTSController(const std::shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIPureMCTSController::GetPlayerInput()
{
	const ID id = player->GetPlayerID();
	Map& map = player->GetGameMap();
	const int maxSimulation = 1000000;

	Column maxColumn = 0;
	float maxWinningRate = -1;
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

		Simulation(childMap, maxSimulation, numSimulation, totalWin);

		float winningRate = (float)totalWin / numSimulation;

		if (winningRate > maxWinningRate)
		{
			maxColumn = column;
			maxWinningRate = winningRate;
		}

		cout << "numSimulation : " << numSimulation << " totalWin : " << totalWin << " Winning Rate : " << winningRate << endl;
	}
	cout << "시뮬레이션들 중 가장 높은 승률을 가진 자식을 선택한다." << endl;

	return maxColumn;
}

void AIPureMCTSController::Simulation(Map& childMap, int maxSimulation, int& numSimulation, int& totalWin)
{
	const ID id = player->GetPlayerID();

#pragma omp parallel for
	for (int i = 0; i < maxSimulation; i++)
	{

		ID currentID = id;
		Map map = childMap;
		Coord lastMove = map.lastMove;

		while (!(map.IsGameEnd(lastMove, currentID) || map.IsMapFull()))
		{
			currentID = currentID ^ 1;
			Column validColumns[MAX_COLUMN];
			int numOfValidColumns = 0;

			for (Column column = 0; column < MAX_COLUMN; column++)
			{
				if (!map.IsColumnValid(column))
					continue;

				validColumns[numOfValidColumns++] = column;
			}

			if (numOfValidColumns == 0)
			{
				cout << "Un Error Occured 1" << endl;
				CommandlineRenderer::Dump(map);
				break;
			}

			int randomIndex = RandomGenerator<XOR128>::Random(0, numOfValidColumns - 1);
			if (randomIndex >= numOfValidColumns)
			{
				cout << "randomIndex >= numOfValidColumns" << endl;
				break;
			}

			Column randomColumn = validColumns[randomIndex];

			bool isValid = false;
			Coord randomCoord = map.GetEmptyCoord(randomColumn, isValid);
			if (!isValid)
			{
				cout << "Un Error Occured Coord : " << randomCoord.first << ", " << randomCoord.second << endl;
				CommandlineRenderer::Dump(map);
				break;
			}

			map.SetCoord(currentID, randomCoord);
			lastMove = randomCoord;
		}

		if (map.winID == id)
		{
#pragma omp atomic
			totalWin++;
		}
#pragma omp atomic
		numSimulation++;
	}
}
