#include "Map.h"

Map::Map()
{
	for (auto & column : data)
	{
		for (int & row : column)
		{
			row = EMPTY_ID;
		}
	}
}

bool Map::IsMapFull()
{
	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		for (Row row = 0; row < MAX_ROW; row++)
		{
			if (data[column][row] == EMPTY_ID)
				return false;
		}
	}
	return true;
}

Coord Map::GetCoord(const Column column, bool& isValid)
{
	for (Row row = 0; row < MAX_ROW; row++)
	{
		if (data[column][row] != EMPTY_ID)
			continue;

		isValid = true;
		return Coord(column, row);
	}

	isValid = false;
	return Coord();
}

void Map::SetCoord(const ID id, const Coord& coord)
{
	data[coord.first][coord.second] = id;
}
