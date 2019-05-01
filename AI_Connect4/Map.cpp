#include "Map.h"
#include <iostream>

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

void Map::GetNumOfNeighbors(const Coord coord, const ID id, std::vector<int>& neighbors, bool selfContained)
{
	const Column& column = coord.first;
	const Row& row = coord.second;

	for (int neighborColumn = column - 1; neighborColumn <= column + 1; neighborColumn++)
	{
		for (int neighborRow = row - 1; neighborRow <= row; neighborRow++)
		{
			if (!CheckCoordIsInBound(neighborColumn, neighborRow))
				continue;

			if (neighborColumn == column && neighborRow == row)
				continue;

			int deltaColumn = neighborColumn - column;
			int deltaRow = neighborRow - row;
			int numOfNeighbor = GetNumOfNeighbor(coord, deltaColumn, deltaRow, id) + GetNumOfNeighbor(coord, -deltaColumn, -deltaRow, id) + (selfContained ? 1 : 0);
			neighbors.push_back(numOfNeighbor);
		}
	}
}

int Map::GetNumOfNeighbor(const Coord originCoord, const int deltaColumn, const int deltaRow, const ID id)
{
	Coord neighborCoord = Coord(originCoord.first + deltaColumn, originCoord.second + deltaRow);
	const Column& neighborColumn = neighborCoord.first;
	const Row& neighborRow = neighborCoord.second;

	if (!CheckCoordIsInBound(neighborColumn, neighborRow))
		return 0;

	if (data[neighborColumn][neighborRow] == id)
		return GetNumOfNeighbor(neighborCoord, deltaColumn, deltaRow, id) + 1;

	return 0;
}

bool Map::CheckCoordIsInBound(const Column column, const Row row)
{
	if (column >= MAX_COLUMN || column < 0)
		return false;

	if (row >= MAX_ROW || row < 0)
		return false;

	return true;
}
