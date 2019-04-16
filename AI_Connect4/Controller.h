#ifndef H_CONTROLLER
#define H_CONTROLLER
#include "Type.h"

class Controller
{

public:
	enum class Type { KEYBOARD, COMPUTER };


	virtual Coord GetPlayerInput() = 0;


};


#endif
