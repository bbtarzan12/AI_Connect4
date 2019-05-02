#include "Game.h"
#include "CommandLineRenderer.h"
#include "KeyboardController.h"
#include "AIAlphaBetaController.h"
#include <iostream>
#include "AIMCTSController.h"


int main()
{
	std::shared_ptr<Game> game = Game::Create();
	std::unique_ptr<Renderer> renderer = Renderer::MakeRenderer(Renderer::Type::COMMAND);

	game->Initialize();

	game->AddPlayer<KeyboardController>("First");
	game->AddPlayer<AIAlphaBetaController>("Second");

	while (!game->isGameFinished())
	{
		game->Update();
		renderer->Render(game);
	}

	game->Release();
	return 0;
}