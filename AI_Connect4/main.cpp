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
	cout << "1. AlphaBeta (Depth 11 고정)" << endl;
	cout << "2. MCTS UCT" << endl;
	cout << "3. MCTS Pure" << endl;
	cout << "4. MCTS Pure GPU (GPU버전 Pure MCTS)" << endl;
	cout << "5. Random (테스트용 완전 렌덤 AI)" << endl;
	cout << "6. Keyboard (사람이 플레이할 때 사용)" << endl;
	cout << "Select controller : ";

	while (!(cin >> ai) || ai <= 0 || ai > 6)
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
	cout << "AI_Connect 4 (COSE361 중간 과제)" << endl;
	cout << "팀원 : 송은재, 박진영" << endl;
	cout << "본 프로젝트는 Visual Studio 2017, C++, Cuda 10.1 로 작성되었습니다." << endl;
	cout << "총 5개의 AI가 있으며 그 중 AlphaBeta와 GPU버전 Pure MCTS가 가장 성능이 좋습니다." << endl << endl;

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
	system("pause");
	return 0;
}