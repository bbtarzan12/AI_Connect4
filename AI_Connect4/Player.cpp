#include "Player.h"
#include "Controller.h"

#include "KeyboardController.h"
#include "AIRandomController.h"
#include "Game.h"

using namespace std;


Player::Player(ID id, std::string name, const std::shared_ptr<Game>& game)
	:id(id), name(name), game(game)
{

}

void Player::SetController(std::shared_ptr<Controller>& controller)
{
	this->controller = std::move(controller);
}

Column Player::GetPlayerInput()
{
	return controller->GetPlayerInput();
}

const ID& Player::GetPlayerID() const
{
	return id;
}

Map& Player::GetGameMap() const
{
	// gameÀÌ nullÀÌ¸é???!!!
	return game->GetGameMap();
}
