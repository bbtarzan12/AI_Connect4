#ifndef H_AIMOSTWINNINGLINECONTROLLER
#define H_AIMOSTWINNINGLINECONTROLLER

#include "Type.h"
#include "Controller.h"

class AIMostWinningLineController : public Controller
{

public:
	AIMostWinningLineController(const std::shared_ptr<Player>& player);
	virtual Column GetPlayerInput() override;

};

#endif
