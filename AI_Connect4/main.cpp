#include "Game.h"
#include "CommandLineRenderer.h"
#include "KeyboardController.h"
#include "AIAlphaBetaController.h"
#include <iostream>
#include "AIMCTSController.h"
#include "AIPureMCTSController.h"


int main()
{
	std::shared_ptr<Game> game = Game::Create();
	std::unique_ptr<Renderer> renderer = Renderer::MakeRenderer(Renderer::Type::COMMAND);

	game->Initialize();

	game->AddPlayer<AIAlphaBetaController>("Alpha Beta");
	game->AddPlayer<AIPureMCTSController>("Pure MCTS");

	while (!game->isGameFinished())
	{
		game->Update();
		renderer->Render(game);
	}

	game->Release();

	return 0;
}