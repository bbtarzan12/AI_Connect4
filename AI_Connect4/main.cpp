#include "Game.h"
#include "CommandLineRenderer.h"


int main()
{
	Game game;
	CommandlineRenderer renderer;

	game.Initialize();

	game.AddPlayer("First", Controller::Type::KEYBOARD);
	game.AddPlayer("Second", Controller::Type::KEYBOARD);

	while (!game.isGameFinished())
	{
		game.Update();
		renderer.Render(game);
	}

	game.Release();
	return 0;
}