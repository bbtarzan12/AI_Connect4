#include "AIMostWinningLineController.h"

AIMostWinningLineController::AIMostWinningLineController(const std::shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIMostWinningLineController::GetPlayerInput()
{
	return Column();
}
