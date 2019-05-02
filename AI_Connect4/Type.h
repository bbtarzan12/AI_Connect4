#ifndef H_COMMONTYPE
#define H_COMMONTYPE

#include <utility>

using Coord = std::pair<int, int>;
using ID = int;
using Column = int;
using Row = int;
using Score = int;

constexpr Column MAX_COLUMN = 7;
constexpr Row MAX_ROW = 6;
constexpr ID EMPTY_ID = -1;
constexpr Score MIN_SCORE = -100000;
constexpr Score MAX_SCORE = 100000;

using ScoreArray = Score[MAX_COLUMN];

#endif
