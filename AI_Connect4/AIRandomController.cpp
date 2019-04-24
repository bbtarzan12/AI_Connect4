#include "AIRandomController.h"
#include "Random.h"
#include "Player.h"

using namespace std;

AIRandomController::AIRandomController(const std::shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIRandomController::GetPlayerInput()
{
	return Column(RandomGenerator<XOR128>::Random(0, 6));
}

