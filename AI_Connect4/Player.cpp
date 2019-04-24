#include "Player.h"
#include "Controller.h"

#include "KeyboardController.h"
#include "AIRandomController.h"
#include "Game.h"

using namespace std;


Player::Player(ID id, std::string name, const Controller::Type type, const std::shared_ptr<Game>& game)
	:id(id), name(name), game(game)
{

}

void Player::AddController(const Controller::Type type)
{
	switch (type)
	{
		case Controller::Type::KEYBOARD:
			controller = make_shared<KeyboardController>(shared_from_this());
			break;
		case Controller::Type::RANDOM:
			controller = make_shared<AIRandomController>(shared_from_this());
			break;
		default:
			break;
	}
}

std::shared_ptr<Player> Player::Create(ID id, std::string name, const Controller::Type type, const std::shared_ptr<Game>& game)
{
	shared_ptr<Player> player = make_shared<Player>(Player(id, name, type, game));
	player->AddController(type);
	return player;
}

Column Player::GetPlayerInput()
{
	return controller->GetPlayerInput();
}

const ID& Player::GetPlayerID() const
{
	return id;
}

const Map& Player::GetGameMap() const
{
	// gameÀÌ nullÀÌ¸é???!!!
	return game->GetGameMap();
}
