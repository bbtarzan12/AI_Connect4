#ifndef H_MAP
#define H_MAP

#include "Type.h"

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
	bool IsMapFull() const;
	Coord GetEmptyCoord(const Column column, bool& isValid) const;
	Coord GetSurfaceCoord(const Column column) const;
	void SetCoord(const ID id, const Coord coord);
	void RemoveCoord(const Coord coord);

};

#endif
