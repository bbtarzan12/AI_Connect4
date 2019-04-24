#ifndef H_AIMOSTWINNINGLINECONTROLLER
#define H_AIMOSTWINNINGLINECONTROLLER

#include "Type.h"
#include "Controller.h"

class AIMostWinningLineController : public Controller
{

public:

	virtual Column GetPlayerInput() override;

};

#endif
