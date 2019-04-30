#ifndef H_HEURISTIC
#define H_HEURISTIC

#include "Type.h"
#include <memory>
#include "Map.h"

class Heuristic
{
public:
	static Score Dumb(Map& map, const ID id);


};

#endif
