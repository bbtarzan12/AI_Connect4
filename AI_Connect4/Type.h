#ifndef H_COMMONTYPE
#define H_COMMONTYPE

#include <utility>

using Coord = std::pair<int, int>;
using ID = int;
using Column = int;
using Row = int;

constexpr Column MAX_COLUMN = 7;
constexpr Row MAX_ROW = 6;
constexpr ID EMPTY_ID = -1;

using Map = ID[MAX_COLUMN][MAX_ROW];

#endif
