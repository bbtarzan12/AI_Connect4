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
	cout << "Input(0 ~ 6) : ";

	if (!(cin >> choice))
	{
		cin.clear();
		cin.ignore();
		cout << "Incorrect input. Try again : ";
	}

	return choice;
}