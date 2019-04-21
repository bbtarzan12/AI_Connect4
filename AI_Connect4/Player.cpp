#include "Player.h"
#include "Controller.h"

#include "KeyboardController.h"
#include "RandomAIController.h"

using namespace std;


Player::Player(ID id, std::string name, const Controller::Type type)
	:id(id), name(name)
{
	switch (type)
	{
		case Controller::Type::KEYBOARD:
			controller = make_shared<KeyboardController>();
			break;
		case Controller::Type::RANDOM:
			controller = make_shared<RandomAIController>();
			break;
		default:
			break;
	}
}

Column Player::GetPlayerInput()
{
	return controller->GetPlayerInput();
}

const ID& Player::GetPlayerID() const
{
	return id;
}
