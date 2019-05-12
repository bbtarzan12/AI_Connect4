#include "Heuristic.h"
#include "Type.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "CommandLineRenderer.h"

using namespace std;

Score Heuristic::Median(Map* map, const Coord coord, const ID currentID)
{
	const ID opponentID = currentID ^ 1;

	Score score = 0;
	Score reward = 0, threat = 0;

	Score reward_op = 0, threat_op = 0;

	reward = Heuristic::Reward(map, coord, currentID);
	reward_op = Heuristic::Reward(map, coord, opponentID);

	Coord threatCoord = Coord(coord.first, coord.second + 1);
	if (map->CheckCoordIsInBound(threatCoord.first, threatCoord.second))
	{
		map->SetCoord(opponentID, threatCoord);
		threat = Heuristic::Threat(map, threatCoord, opponentID);
		map->RemoveCoord(threatCoord);
	}

	if (map->CheckCoordIsInBound(threatCoord.first, threatCoord.second))
	{
		map->SetCoord(currentID, threatCoord);
		threat_op = Heuristic::Threat(map, threatCoord, currentID);
		map->RemoveCoord(threatCoord);
	}
	map->RemoveCoord(coord);

	score = reward + threat - threat_op * 3 - reward_op * 5;
	return score;
}

Score Heuristic::Reward(Map* map, const Coord coord, const ID id)
{
	Score score = 0;
	int numOfNeighbors[7] = { 0, 0, 0, 0, 0, 0, 0 };
	map->GetNumOfNeighbors(coord, id, numOfNeighbors);
	for (auto & numOfNeighbor : numOfNeighbors)
	{
		score += GetNeighborRewardScore(numOfNeighbor);
	}

	return score;
}

Score Heuristic::Defense(Map* map, const Coord coord, const ID id)
{
	Score score = 0;
	int numOfNeighbors[7] = { 0, 0, 0, 0, 0, 0, 0 };
	map->GetNumOfNeighbors(coord, id, numOfNeighbors);

	for (auto & numOfNeighbor : numOfNeighbors)
	{
		score += GetNeighborDefenseScore(numOfNeighbor);
	}

	return score;
}

Score Heuristic::Threat(Map* map, const Coord coord, const ID id)
{
	Score score = 0;
	int numOfNeighbors[7] = { 0, 0, 0, 0, 0, 0, 0 };
	map->GetNumOfNeighbors(coord, id, numOfNeighbors);

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
		case 0:
		case 1: return 1;
		case 2: return 20;
		case 3: return 40;
		default: return 999;
	}
}

Score Heuristic::GetNeighborDefenseScore(const int numOfNeighbor)
{
	switch (numOfNeighbor)
	{
		case 0:
		case 1: return 10;
		case 2: return 50;
		case 3: return 100;
		default: return 999;
	}
}

Score Heuristic::GetNeighborThreatScore(const int numOfNeighbor)
{
	switch (numOfNeighbor)
	{
		case 0:
		case 1: return 0;
		case 2: return 10;
		case 3: return 20;
		default: return 999;
	}
}

