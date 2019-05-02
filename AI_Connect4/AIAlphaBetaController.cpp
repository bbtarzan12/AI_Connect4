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
	Tree tree(map, id, 9);
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

	root = new Node(map);
	//cout << AlphaBetaPruning(root, 1, MIN_SCORE, MAX_SCORE, true) << endl;
	cout << NegaMax(root, 1, MIN_SCORE, MAX_SCORE, true) << endl;

	Score maxScore = MIN_SCORE;
	Column maxColumn = 0;
	for (auto & child : root->childs)
	{
		if(child->score < maxScore)
			continue;

		maxScore = child->score;
		maxColumn = child->column;
	}

	for (auto & child : root->childs)
	{
		cout << "Coord : " << child->coord.first << ", " << child->coord.second << "  Score : " << child->score << endl;
	}
	return maxColumn;
}

Score AIAlphaBetaController::Tree::AlphaBetaPruning(Node* node, int depth, Score alpha, Score beta, bool isMaximizingPlayer)
{
	const ID currentID = !isMaximizingPlayer ? id : id ^ 1;

	if (node->map.IsGameEnd(node->coord, currentID))
	{
		node->score = (!isMaximizingPlayer) ? MAX_SCORE : MIN_SCORE;
		return node->score;
	}

	if (depth > maxDepth)
	{
		////cout << node << endl;
		//const ID opponentID = !isMaximizingPlayer ? id ^ 1 : id;

		//Coord& coord = node->coord;
		//Map& map = node->map;
		//Score score = 0;
		//Score reward = 0, defense = 0, threat = 0;

		//map.SetCoord(currentID, coord);	

		//reward = Heuristic::Reward(map, coord, currentID);

		//Coord threatCoord = Coord(coord.first, coord.second + 1);
		//if (map.CheckCoordIsInBound(threatCoord.first, threatCoord.second))
		//{
		//	map.SetCoord(opponentID, threatCoord);
		//	threat = Heuristic::Threat(map, threatCoord, opponentID);
		//	map.RemoveCoord(threatCoord);
		//}
		//map.RemoveCoord(coord);

		//map.SetCoord(opponentID, coord);
		//defense = Heuristic::Defense(map, coord, opponentID);
		//map.RemoveCoord(coord);

		//map.SetCoord(currentID, coord);

		//score = reward + defense - threat;
		//node->score = score;
		////cout << "Leaf " << score << " " << currentID << " " << opponentID << endl;
		////cout << "Reward : " << reward << " Defense : " << defense << " Threat : " << threat << endl;
		//return score * ((!isMaximizingPlayer) ? 1 : -1);

		Score score = Heuristic::Dumb(node->map, node->coord, currentID);
		node->score = score * ((!isMaximizingPlayer) ? 1 : -1);
		return node->score;
	}

	for (Column column = 0; column < MAX_COLUMN; column++)
	{

		bool isvalid = false;
		Coord coord = node->map.GetEmptyCoord(column, isvalid);
		if (!isvalid)
		{
			continue;
		}

		ID childId = isMaximizingPlayer ? id : id ^ 1;
		Node* childNode = new Node(node->map);
		childNode->column = column;
		childNode->coord = coord;
		childNode->map.SetCoord(childId, coord);
		node->childs.push_back(childNode);
		//cout << "Child " << column << endl;
		//CommandlineRenderer::Dump(childNode->map);
	}

	//if (isMaximizingPlayer)
	//{
	//	Score best = MIN_SCORE;

	//	for (auto & child : node->childs)
	//	{
	//		Score score = GetAlphaBetaValue(child, depth + 1, alpha, beta, false);
	//		best = max(best, score);
	//		alpha = max(alpha, best);
	//		//cout << "Child Maximize " << best << endl;
	//		if (beta <= alpha)
	//			break;
	//	}
	//	node->score = best;
	//	//cout << node << " is " << best << endl;
	//	return best;
	//}
	//else
	//{
	//	Score best = MAX_SCORE;

	//	for (auto & child : node->childs)
	//	{
	//		Score score = GetAlphaBetaValue(child, depth + 1, alpha, beta, true);
	//		best = min(best, score);
	//		beta = min(beta, best);
	//		//cout << "Child Minimize " << best << endl;
	//		if (beta <= alpha)
	//			break;
	//	}
	//	node->score = best;
	//	//cout << node << " is " << best << endl;
	//	return best;
	//}

	if (isMaximizingPlayer)
	{
		for (auto & child : node->childs)
		{
			alpha = max(alpha, AlphaBetaPruning(child, depth + 1, alpha, beta, false));
			if (beta <= alpha)
				break;
		}
		node->score = alpha;
		return alpha;
	}
	else
	{
		for (auto & child : node->childs)
		{
			beta = min(beta, AlphaBetaPruning(child, depth + 1, alpha, beta, true));
			if (beta <= alpha)
				break;
		}
		node->score = beta;
		return beta;
	}
}

Score AIAlphaBetaController::Tree::NegaMax(Node* node, int depth, Score alpha, Score beta, bool isMaximizingPlayer)
{
	const ID currentID = isMaximizingPlayer ? id : id ^ 1;

	if (node->map.IsGameEnd(node->coord, currentID))
	{
		node->score = (!isMaximizingPlayer) ? MAX_SCORE : MIN_SCORE;
		return node->score;
	}

	if (depth > maxDepth)
	{
		Score score = Heuristic::Dumb(node->map, node->coord, currentID);
		node->score = score * ((!isMaximizingPlayer) ? 1 : -1);
		return node->score;
	}

	for (Column column = 0; column < MAX_COLUMN; column++)
	{

		bool isvalid = false;
		Coord coord = node->map.GetEmptyCoord(column, isvalid);
		if (!isvalid)
		{
			continue;
		}

		ID childId = isMaximizingPlayer ? id : id ^ 1;
		Node* childNode = new Node(node->map);
		childNode->column = column;
		childNode->coord = coord;
		childNode->map.SetCoord(childId, coord);
		node->childs.push_back(childNode);
	}

	for (auto & child : node->childs)
	{
		alpha = max(alpha, -NegaMax(child, depth + 1, -beta, -alpha, !isMaximizingPlayer));
		if (beta <= alpha)
		{
			node->score = beta;
			return node->score;
		}
	}
	node->score = alpha;
	return node->score;
}
