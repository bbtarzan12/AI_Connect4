#ifndef H_AIRANDOMCONTROLLER
#define H_AIRANDOMCONTROLLER

#include "Type.h"
#include "Controller.h"

class AIRandomController : public Controller
{

public:
	AIRandomController(const std::shared_ptr<Player>& player);
	virtual Column GetPlayerInput() override;

};

#endif
