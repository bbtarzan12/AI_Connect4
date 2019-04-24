#ifndef H_KEYBOARDCONTROLLER
#define H_KEYBOARDCONTROLLER

#include "Type.h"
#include "Controller.h"

class KeyboardController : public Controller
{

public:
	KeyboardController(const std::shared_ptr<Player>& player);
	virtual Column GetPlayerInput() override;

};

#endif
