#include "RandomAIController.h"
#include "Random.h"

using namespace std;

Column RandomAIController::GetPlayerInput()
{
	return Column(RandomGenerator<XOR128>::Random(0, 6));
}

