#include "Game.h"
#include "CommandLineRenderer.h"

int main()
{
	Game game;
	std::unique_ptr<Renderer> renderer = Renderer::MakeRenderer(Renderer::Type::COMMAND);

	game.Initialize();

	game.AddPlayer("First", Controller::Type::RANDOM);
	game.AddPlayer("Second", Controller::Type::RANDOM);

	while (!game.isGameFinished())
	{
		game.Update();
		renderer->Render(game);
	}

	game.Release();
	return 0;
}