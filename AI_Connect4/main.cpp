#include "Game.h"
#include "CommandLineRenderer.h"
#include "KeyboardController.h"
#include "AIAlphaBetaController.h"
#include "AIMCTSController.h"
#include "AIPureMCTSController.h"
#include "AIRandomController.h"
#include "AIPureMCTSCudaController.h"

#include <iostream>
#include <string>

using namespace std;


void SetPlayer(const shared_ptr<Game>& game)
{
	string name;
	cout << "Player Name : ";
	while (!(getline(cin, name)) || name.empty())
	{
		cin.clear();
		cin.ignore();
		cout << "Incorrect input. Try again : ";
	}

	int ai;
	cout << "1. AlphaBeta" << endl;
	cout << "2. MCTS UCT" << endl;
	cout << "3. MCTS Pure" << endl;
	cout << "4. MCTS Pure GPU" << endl;
	cout << "5. Random" << endl;
	cout << "6. Keyboard" << endl;
	cout << "Select controller : ";

	while (!(cin >> ai) || ai <= 0 || ai > 5)
	{
		cin.clear();
		cin.ignore();
		cout << "Incorrect input. Try again : ";
	}

	switch (ai)
	{
		case 1:
			game->AddPlayer<AIAlphaBetaController>(name);
			break;
		case 2:
			game->AddPlayer<AIMCTSController>(name);
			break;
		case 3:
			game->AddPlayer<AIPureMCTSController>(name);
			break;
		case 4:
			game->AddPlayer<AIPureMCTSCudaController>(name);
			break;
		case 5:
			game->AddPlayer<AIRandomController>(name);
			break;
		case 6:
			game->AddPlayer<KeyboardController>(name);
			break;
	}
	cin.ignore();
}

int main()
{
	std::shared_ptr<Game> game = Game::Create();
	std::unique_ptr<Renderer> renderer = Renderer::MakeRenderer(Renderer::Type::COMMAND);

	game->Initialize();

	SetPlayer(game);
	SetPlayer(game);

	while (!game->IsGameFinished())
	{
		game->Update();
		renderer->Render(game);
	}

	game->Release();

	return 0;
}