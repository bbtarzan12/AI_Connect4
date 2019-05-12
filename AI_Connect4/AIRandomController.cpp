#include "AIRandomController.h"
#include "Random.h"
#include "Player.h"
#include <iostream>

using namespace std;

AIRandomController::AIRandomController(const std::shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIRandomController::GetPlayerInput()
{
	cout << "테스트용 랜덤 선택을 하는 AI" << endl;
	return Column(RandomGenerator<XOR128>::Random(0, 6));
}

