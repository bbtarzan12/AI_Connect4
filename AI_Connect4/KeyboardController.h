#ifndef H_KEYBOARDCONTROLLER
#define H_KEYBOARDCONTROLLER

#include "Type.h"
#include "Controller.h"

class KeyboardController : public Controller
{

public:
	virtual Coord GetPlayerInput() override;

};

#endif
