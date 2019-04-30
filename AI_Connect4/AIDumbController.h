#ifndef H_AIDUMBCONTROLLER
#define H_AIDUMBCONTROLLER

#include "Type.h"
#include "Controller.h"

class AIDumbController : public Controller
{

public:
	AIDumbController(const std::shared_ptr<Player>& player);
	virtual Column GetPlayerInput() override;

};

#endif
