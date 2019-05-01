#include "Heuristic.h"
#include "Type.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
		case 1: return 4;
		case 2: return 9;
		default: return 999;
	}
}

Score Heuristic::GetNeighborDefenseScore(const int numOfNeighbor)
{
	return GetNeighborRewardScore(numOfNeighbor);
}

Score Heuristic::GetNeighborThreatScore(const int numOfNeighbor)
{
	switch (numOfNeighbor)
	{
		case 0: return 0;
		case 1: return 2;
		case 2: return 5;
		default: return 999;
	}
}
