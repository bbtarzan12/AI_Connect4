#include "Heuristic.h"
#include "Type.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "CommandLineRenderer.h"

using namespace std;

Score Heuristic::Dumb(Map& map, const Coord coord, const ID currentID)
{
	const ID opponentID = currentID ^ 1;

	Score score = 0;
	Score reward = 0, defense = 0, threat = 0;

	map.SetCoord(currentID, coord);
	reward = Heuristic::Reward(map, coord, currentID);

	vector<Coord> surfaceCoords;
	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		Coord surfaceCoord = map.GetSurfaceCoord(column);
		if(map[surfaceCoord.first][surfaceCoord.second] == currentID)
			continue;
		surfaceCoords.push_back(surfaceCoord);
	}

	for (auto & surfaceCoord : surfaceCoords)
	{
		//map.SetCoord(opponentID, surfaceCoord);
		threat += Heuristic::Threat(map, surfaceCoord, opponentID);
		//map.RemoveCoord(surfaceCoord);
	}
	threat = (float) threat / surfaceCoords.size();

	map.SetCoord(opponentID, coord);
	defense = Heuristic::Defense(map, coord, opponentID);
	map.RemoveCoord(coord);

	map.SetCoord(currentID, coord);

	score = reward + defense - threat;
	//cout << "Leaf " << score << " " << currentID << " " << opponentID << endl;
	//cout << "Reward : " << reward << " Defense : " << defense << " Threat : " << threat << endl;
	//CommandlineRenderer::Dump(map);
	return score;
}

Score Heuristic::Reward(Map& map, const Coord coord, const ID id)
{
	Score score = 0;
	vector<int> numOfNeighbors;
	map.GetNumOfNeighbors(coord, id, numOfNeighbors, false);

	for (auto & numOfNeighbor : numOfNeighbors)
	{
		score += GetNeighborRewardScore(numOfNeighbor);
	}
	
	return score;
}

Score Heuristic::Defense(Map& map, const Coord coord, const ID id)
{
	Score score = 0;
	vector<int> numOfNeighbors;
	map.GetNumOfNeighbors(coord, id, numOfNeighbors, false);

	for (auto & numOfNeighbor : numOfNeighbors)
	{
		score += GetNeighborDefenseScore(numOfNeighbor);
	}

	return score;
}

Score Heuristic::Threat(Map& map, const Coord coord, const ID id)
{
	Score score = 0;
	vector<int> numOfNeighbors;
	map.GetNumOfNeighbors(coord, id, numOfNeighbors, false);

	for (auto & numOfNeighbor : numOfNeighbors)
	{
		score += GetNeighborThreatScore(numOfNeighbor);
	}
	return score;
}

Score Heuristic::GetNeighborRewardScore(const int numOfNeighbor)
{
	switch (numOfNeighbor)
	{
		case 0: return 0;
		case 1: return 3;
		case 2: return 10;
		default: return 999;
	}
}

Score Heuristic::GetNeighborDefenseScore(const int numOfNeighbor)
{
	switch (numOfNeighbor)
	{
		case 0: return 0;
		case 1: return 8;
		case 2: return 40;
		default: return 999;
	}
}

Score Heuristic::GetNeighborThreatScore(const int numOfNeighbor)
{
	switch (numOfNeighbor)
	{
		case 0: return 0;
		case 1: return 16;
		case 2: return 81;
		default: return 999;
	}
}
