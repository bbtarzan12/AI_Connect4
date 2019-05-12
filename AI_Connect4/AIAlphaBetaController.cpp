#include "AIAlphaBetaController.h"
#include "Heuristic.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include "CommandLineRenderer.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

AIAlphaBetaController::AIAlphaBetaController(const shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIAlphaBetaController::GetPlayerInput()
{
	auto start = high_resolution_clock::now();

	Map& map = player->GetGameMap();
	const ID id = player->GetPlayerID();
	Map copiedMap = map;
	Tree tree(copiedMap, id, 11);
	Column result = tree.GetMaxScoreColumn();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << duration.count() / 1000.0f << "초 걸렸습니다" << endl;
	return result;
}

AIAlphaBetaController::Tree::Tree(Map map, const ID id, const int maxDepth)
	: map(map), id(id), maxDepth(maxDepth)
{

}

Column AIAlphaBetaController::Tree::GetMaxScoreColumn()
{
	root = Node();
	root.map = &map;
	root.id = id ^ 1;
	Score score = AlphaBetaPruning(&root, 1, MINUS_INFINITE, PLUS_INFINITE, true);

	cout << "Alpha Beta Pruning을 Depth " << maxDepth << " 까지 진행한 결과" << endl;
	cout << "맨 처음 루트의 자식들(" << root.childs.size() << "개) 중 가장 점수가 높은 자식을 선택했다." << endl;
	cout << "휴리스틱 점수 : " << score << endl;

	return bestNode->coord.first;
}

Score AIAlphaBetaController::Tree::AlphaBetaPruning(Node* node, int depth, Score alpha, Score beta, bool isMaximizingPlayer)
{
	if (depth != 1 && node->map->IsGameEnd(node->coord, node->id))
	{
		return (node->id == id) ? MAX_SCORE : MIN_SCORE;
	}

	if (depth > maxDepth)
	{
		return Heuristic::Dumb(node->map, node->coord, node->id) * (node->id == id ? 1 : -1);
	}

	if (depth != 1 && node->map->IsMapFull())
	{
		return 0;
	}

	int numOfEmptyTop = node->map->GetNumOfEmptyTop();
	node->childs.reserve(numOfEmptyTop);
	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		bool isvalid = false;
		Coord coord = node->map->GetEmptyCoord(column, isvalid);
		if (!isvalid)
		{
			continue;
		}

		Node* childNode = new Node();
		childNode->map = node->map;
		childNode->id = node->id ^ 1;
		childNode->coord = coord;
		node->childs.push_back(childNode);
	}

	if (isMaximizingPlayer)
	{
		Score best = MINUS_INFINITE;

		for (auto & child : node->childs)
		{
			child->map->SetCoord(child->id, child->coord);
			Score score = AlphaBetaPruning(child, depth + 1, alpha, beta, false);
			child->map->RemoveCoord(child->coord);


			Score oldBest = best;

			best = max(best, score);
			alpha = max(alpha, best);

			if (depth == 1 && oldBest != best)
			{
				bestNode = child;
			}

			if (beta <= alpha)
				break;
		}
		return best;
	}
	else
	{
		Score best = PLUS_INFINITE;

		for (auto & child : node->childs)
		{
			child->map->SetCoord(child->id, child->coord);
			Score score = AlphaBetaPruning(child, depth + 1, alpha, beta, true);
			child->map->RemoveCoord(child->coord);

			best = min(best, score);
			beta = min(beta, best);
			if (beta <= alpha)
				break;
		}
		return best;
	}
}