#include "AIDumbController.h"
#include "Heuristic.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

using namespace std;

AIDumbController::AIDumbController(const shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIDumbController::GetPlayerInput()
{
	Map& map = player->GetGameMap();
	const ID id = player->GetPlayerID();
	const ID opponentID = id ^ 1; // Todo : Game의 Player Vector를 그냥 player 1, 2로 바꾸자

	ScoreArray scoreArray;

	for (Column column = 0; column < MAX_COLUMN; column++)
	{

		bool isvalid = false;
		Coord coord = map.GetEmptyCoord(column, isvalid);
		if (!isvalid)
		{
			scoreArray[column] = -1;
			continue;
		}

		Score score = 0;

		map.SetCoord(id, coord);
		score += Heuristic::Reward(map, coord, id);

		Coord threatCoord = Coord(coord.first, coord.second + 1);
		if (map.CheckCoordIsInBound(threatCoord.first, threatCoord.second))
		{
			score -= Heuristic::Threat(map, threatCoord, opponentID);
		}
		map.RemoveCoord(coord);


		map.SetCoord(opponentID, coord);
		score += Heuristic::Defense(map, coord, opponentID);
		map.RemoveCoord(coord);


		scoreArray[column] = score;
	}

	Column maxHeuristicColumn = (max_element(scoreArray, scoreArray + MAX_COLUMN) - scoreArray);

	return maxHeuristicColumn;
}
