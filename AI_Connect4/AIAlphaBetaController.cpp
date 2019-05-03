#include "AIAlphaBetaController.h"
#include "Heuristic.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include "CommandLineRenderer.h"

using namespace std;

AIAlphaBetaController::AIAlphaBetaController(const shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIAlphaBetaController::GetPlayerInput()
{
	Map& map = player->GetGameMap();
	const ID id = player->GetPlayerID();
	Tree tree(map, id, 10);
	return tree.GetMaxScoreColumn();
}

AIAlphaBetaController::Tree::Tree(Map map, const ID id, const int maxDepth)
	: map(map), id(id), maxDepth(maxDepth)
{

}

Column AIAlphaBetaController::Tree::GetMaxScoreColumn()
{
	root = Node(map);
	root.id = id ^ 1;
	AlphaBetaPruning(&root, 1, MINUS_INFINITE, PLUS_INFINITE, true);
	return bestNode->column;
}

Score AIAlphaBetaController::Tree::AlphaBetaPruning(Node* node, int depth, Score alpha, Score beta, bool isMaximizingPlayer)
{
	if (depth != 1 && node->map.IsGameEnd(node->coord, node->id))
	{
		return (node->id == id) ? MAX_SCORE : MIN_SCORE;
	}

	if (depth > maxDepth)
	{
		return Heuristic::Dumb(node->map, node->coord, node->id) * (node->id == id ? 1 : -1);
	}


	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		bool isvalid = false;
		Coord coord = node->map.GetEmptyCoord(column, isvalid);
		if (!isvalid)
		{
			continue;
		}

		Node* childNode = new Node(node->map);
		childNode->id = node->id ^ 1;
		childNode->column = column;
		childNode->coord = coord;
		childNode->map.SetCoord(childNode->id, coord);
		node->childs.push_back(childNode);
	}

	if (isMaximizingPlayer)
	{
		Score best = MINUS_INFINITE;

		for (auto & child : node->childs)
		{
			Score score = AlphaBetaPruning(child, depth + 1, alpha, beta, false);
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
			Score score = AlphaBetaPruning(child, depth + 1, alpha, beta, true);
			best = min(best, score);
			beta = min(beta, best);
			if (beta <= alpha)
				break;
		}
		return best;
	}
}