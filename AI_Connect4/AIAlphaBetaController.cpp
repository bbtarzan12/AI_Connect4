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
	Tree tree(map, id, 7);
	return tree.GetMaxScoreColumn();
}

AIAlphaBetaController::Tree::Tree(Map map, const ID id, const int maxDepth)
	: map(map), id(id), maxDepth(maxDepth)
{

}

Column AIAlphaBetaController::Tree::GetMaxScoreColumn()
{
	//Column maxColumn = 0;
	//Score maxScore = MIN_SCORE;
	//for (Column column = 0; column < MAX_COLUMN; column++)
	//{

	//	bool isvalid = false;
	//	Coord coord = map.GetEmptyCoord(column, isvalid);
	//	if (!isvalid)
	//	{
	//		continue;
	//	}

	//	Map newMap = map;
	//	newMap.SetCoord(id, coord);
	//	root = new Node(newMap);
	//	root->coord = coord;
	//	Score score = GetAlphaBetaValue(root, 1, MIN_SCORE, MAX_SCORE, true);
	//	delete root;
	//	cout << "Coord : " << coord.first << ", " << coord.second << "  Score : " << score << endl;
	//	if(score < maxScore)
	//		continue;

	//	maxScore = score;
	//	maxColumn = column;
	//}

	root = Node(map);
	root.id = id ^ 1;
	//cout << AlphaBetaPruning(root, 1, MIN_SCORE, MAX_SCORE, true) << endl;
	

	//NegaMax(&root, 0, MIN_SCORE, MAX_SCORE);
	cout << "Root : " << &root << endl;
	AlphaBetaPruning(&root, 1, MINUS_INFINITE, PLUS_INFINITE, true);
	//Node* optimalLeafNode = bestNode;
	//while (optimalLeafNode->parent != &root)
	//	optimalLeafNode = optimalLeafNode->parent;

	//return optimalLeafNode->column;

	return bestNode->column;

	//Score alpha = MIN_SCORE;
	//Score beta = MAX_SCORE;
	//Column bestColumn = 0;
	//for (Column column = 0; column < MAX_COLUMN; column++)
	//{

	//	bool isvalid = false;
	//	Coord coord = root.map.GetEmptyCoord(column, isvalid);
	//	if (!isvalid)
	//	{
	//		continue;
	//	}

	//	Node childNode = Node(root.map);
	//	childNode.id = root.id ^ 1;
	//	childNode.column = column;
	//	childNode.coord = coord;
	//	childNode.map.SetCoord(childNode.id, coord);

	//	alpha = max(alpha, -NegaMax(&childNode, 2, -beta, -alpha));
	//	if (beta <= alpha)
	//	{
	//		cout << alpha << endl;
	//		bestColumn = column;
	//	}
	//}

	//Score maxScore = MIN_SCORE;
	//Column maxColumn = 0;
	//for (auto & child : root.childs)
	//{
	//	if (child->score < maxScore)
	//		continue;

	//	maxScore = child->score;
	//	maxColumn = child->column;
	//}

	//for (auto & child : root.childs)
	//{
	//	cout << "Coord : " << child->coord.first << ", " << child->coord.second << "  Score : " << child->score << endl;
	//}

	//return maxColumn;

	//return bestColumn;
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
		childNode->parent = node;
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
				bestNode->score = score;
				//cout << bestNode->score << " " << bestNode->parent << endl;
				//CommandlineRenderer::Dump(bestNode->map);
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

Score AIAlphaBetaController::Tree::NegaMax(Node* node, int depth, Score alpha, Score beta)
{
	if (node->map.IsGameEnd(node->coord, node->id))
	{
		//node->score = (node->id == id) ? MAX_SCORE : MIN_SCORE;
		//return node->score;
		return (node->id != id) ? MAX_SCORE : MIN_SCORE;
	}

	if (depth >= maxDepth)
	{
		//Score score = Heuristic::Dumb(node->map, node->coord, node->id);
		//node->score = score * (node->id == id ? 1 : -1);
		//return node->score;
		return Heuristic::Dumb(node->map, node->coord, node->id) * (node->id != id ? 1 : -1);
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
		childNode->parent = node;
		childNode->map.SetCoord(childNode->id, coord);
		node->childs.push_back(childNode);
	}

	for (auto & child : node->childs)
	{
		Score score = -NegaMax(child, depth + 1, -beta, -alpha);
		if (score > alpha)
		{
			//if (bestNode == nullptr || bestNode->score > score)
			//{
			//	bestNode = child;
			//	bestNode->score = score;
			//	cout << score << " " << child->parent->column << endl;
			//}
			if (depth == 1)
			{
				if (bestNode == nullptr || bestNode->score > score)
				{
					bestNode = child;
					bestNode->score = score;
					cout << score << " " << child->parent->column << endl;
				}
			}
			alpha = score;
		}
		//alpha = max(alpha, );
		if (beta <= alpha)
		{
			//node->score = beta;
			return beta;
		}
	}
	//node->score = alpha;
	//cout << depth << " " << node->score << endl;
	return alpha;
}
