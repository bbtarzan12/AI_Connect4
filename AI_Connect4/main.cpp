#include "Game.h"
#include "CommandLineRenderer.h"
#include "KeyboardController.h"
#include "AIAlphaBetaController.h"
#include <iostream>
#include "AIMCTSController.h"
#include "AIPureMCTSController.h"
#include "AIPureMCTSCudaController.h"

int main()
{
	std::shared_ptr<Game> game = Game::Create();
	std::unique_ptr<Renderer> renderer = Renderer::MakeRenderer(Renderer::Type::COMMAND);

	game->Initialize();

	game->AddPlayer<AIPureMCTSCudaController>("CUDA MCTS");
	game->AddPlayer<AIAlphaBetaController>("Alpha Beta 11");

	while (!game->isGameFinished())
	{
		game->Update();
		renderer->Render(game);
	}

	game->Release();

	return 0;
}