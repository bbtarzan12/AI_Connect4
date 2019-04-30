#include "Heuristic.h"
#include "Type.h"
#include <iostream>
#include <vector>

using namespace std;

Score Heuristic::Dumb(Map& map, const ID id)
{
	vector<Coord> surfaces;

	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		bool isValid = false;
		Coord coord = map.GetEmptyCoord(column, isValid);

		if (!isValid)
		{
			continue;
		}

		surfaces.push_back(coord);
	}

	for (auto & surface : surfaces)
	{

	}

	return 1;
}
