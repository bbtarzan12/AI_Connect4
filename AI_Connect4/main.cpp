#include "Game.h"


int main()
{
	Game game;

	game.Initialize();

	game.AddPlayer("First", Controller::Type::KEYBOARD);
	game.AddPlayer("Second", Controller::Type::KEYBOARD);

	while (!game.isGameFinished())
	{
		game.Update();
	}

	game.Release();
	return 0;
}