#include "KeyboardController.h"
#include <iostream>

using namespace std;

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