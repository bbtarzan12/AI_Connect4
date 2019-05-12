#ifndef H_HEURISTIC
#define H_HEURISTIC

#include "Type.h"
#include <memory>
#include "Map.h"

class Heuristic
{

public:
	static Score Median(Map* map, const Coord coord, const ID id);

private:
	static Score Reward(Map* map, const Coord coord, const ID id);
	static Score Defense(Map* map, const Coord coord, const ID id);
	static Score Threat(Map* map, const Coord coord, const ID id);

private:
	static Score GetNeighborRewardScore(const int numOfNeighbor);
	static Score GetNeighborDefenseScore(const int numOfNeighbor);
	static Score GetNeighborThreatScore(const int numOfNeighbor);
};

#endif
