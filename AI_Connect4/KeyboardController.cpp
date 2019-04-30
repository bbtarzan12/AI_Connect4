#include "KeyboardController.h"
#include <iostream>

using namespace std;

KeyboardController::KeyboardController(const std::shared_ptr<Player>& player)
{
	this->player = player;
}

Column KeyboardController::GetPlayerInput()
{
	Column choice;
	cout << "Input(1 ~ 7) : ";

	if (!(cin >> choice) || choice <= 0 || choice > 7)
	{
		cin.clear();
		cin.ignore();
		cout << "Incorrect input. Try again : ";
	}

	return choice - 1;
}