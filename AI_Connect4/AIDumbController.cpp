#include "AIDumbController.h"
#include "Heuristic.h"
#include "Player.h"
#include <iostream>

using namespace std;

AIDumbController::AIDumbController(const shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIDumbController::GetPlayerInput()
{
	Map& map = player->GetGameMap();
	const ID& id = player->GetPlayerID();

	ScoreArray scoreArray;

	Map testMap = map;
	for (Column column = 0; column < MAX_COLUMN; column++)
	{

		bool isvalid = false;
		Coord coord = testMap.GetCoord(column, isvalid);
		if (!isvalid)
		{
			scoreArray[column] = -1;
			continue;
		}

		testMap.SetCoord(id, coord);

		scoreArray[column] = Heuristic::Dumb(testMap, id);
	}

	return Column();
}
