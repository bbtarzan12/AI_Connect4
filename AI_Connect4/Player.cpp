#include "Player.h"
#include "Controller.h"

#include "KeyboardController.h"

using namespace std;


Player::Player(ID id, std::string name, const Controller::Type type)
	:id(id), name(name)
{
	switch (type)
	{
		case Controller::Type::KEYBOARD:
			controller = std::make_shared<KeyboardController>();
			break;
		case Controller::Type::COMPUTER:
			break;
		default:
			break;
	}
}

Coord Player::GetPlayerInput()
{
	return controller->GetPlayerInput();
}