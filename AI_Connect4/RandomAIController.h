#ifndef H_RANDOMAICONTROLLER
#define H_RANDOMAICONTROLLER

#include "Type.h"
#include "Controller.h"

class RandomAIController : public Controller
{

public:
	virtual Column GetPlayerInput() override;

};

#endif
