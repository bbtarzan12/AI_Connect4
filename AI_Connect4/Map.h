#ifndef H_MAP
#define H_MAP

#include "Type.h"
#include <vector>

class Map
{
private:
	ID data[MAX_COLUMN][MAX_ROW];
public:
	Map();
	class Rows
	{
		Map& map;
		Column column;
	public:
		Rows(Map& map, const Column column) : map(map), column(column) {}
		ID& operator[](const Row row)
		{
			return map.data[column][row]; 
		}

		const ID& operator[](const Row row) const
		{
			return map.data[column][row];
		}
	};

	Rows operator [](const Column column)
	{
		return Rows(*this, column);
	}

public:
	Coord lastMove;
	ID winID;

public:
	bool IsMapFull();
	Coord GetEmptyCoord(const Column column, bool& isValid) const;
	Coord GetSurfaceCoord(const Column column) const;
	bool IsColumnValid(const Column column) const;
	void SetCoord(const ID id, const Coord coord);
	void RemoveCoord(const Coord coord);
	void GetNumOfNeighbors(const Coord coord, const ID id, std::vector<int>& neighbors, bool selfContained = true);
	bool CheckCoordIsInBound(const Column column, const Row row);
	bool IsGameEnd(const Coord coord, const ID id);

private:
	int GetNumOfNeighbor(const Coord originCoord, const int deltaColumn, const int deltaRow, const ID id);

};

#endif
