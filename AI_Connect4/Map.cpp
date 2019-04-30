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

bool Map::IsMapFull() const
{
	for (const auto & column : data)
	{
		for (int row : column)
		{
			if (row == EMPTY_ID)
				return false;
		}
	}
	return true;
}

Coord Map::GetEmptyCoord(const Column column, bool& isValid) const
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

Coord Map::GetSurfaceCoord(const Column column) const
{
	for (Row row = 0; row < MAX_ROW; row++)
	{
		if (data[column][row] != EMPTY_ID)
			continue;

		return Coord(column, row - 1);
	}

	return Coord(column, MAX_ROW - 1);
}

void Map::SetCoord(const ID id, const Coord coord)
{
	data[coord.first][coord.second] = id;
}

void Map::RemoveCoord(const Coord coord)
{
	data[coord.first][coord.second] = EMPTY_ID;
}
