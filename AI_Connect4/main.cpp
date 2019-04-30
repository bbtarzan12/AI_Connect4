#include "Game.h"
#include "CommandLineRenderer.h"
#include "KeyboardController.h"
#include "AIDumbController.h"
#include <iostream>


int main()
{
	std::shared_ptr<Game> game = Game::Create();
	std::unique_ptr<Renderer> renderer = Renderer::MakeRenderer(Renderer::Type::COMMAND);

	game->Initialize();

	game->AddPlayer<KeyboardController>("First");
	game->AddPlayer<AIDumbController>("Second");

	while (!game->isGameFinished())
	{
		game->Update();
		renderer->Render(game);
	}

	game->Release();
	return 0;
}