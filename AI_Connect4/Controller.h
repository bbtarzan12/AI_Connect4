#ifndef H_CONTROLLER
#define H_CONTROLLER
#include "Type.h"
#include <memory>

class Player;

class Controller
{

public:
	virtual Column GetPlayerInput() = 0;

protected:
	std::shared_ptr<Player> player;
};


#endif
