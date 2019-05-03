#ifndef H_AIALPHABETACONTROLLER
#define H_AIALPHABETACONTROLLER

#include "Type.h"
#include "Controller.h"
#include <vector>
#include "Map.h"

class AIAlphaBetaController : public Controller
{

public:
	AIAlphaBetaController(const std::shared_ptr<Player>& player);
	virtual Column GetPlayerInput() override;

	struct Node
	{
		Node() {}
		Node(Map map) : map(map) { }
		ID id;
		Map map;
		Node* parent = nullptr;
		Coord coord;
		Score score = 0;
		Column column = 0;
		std::vector<Node*> childs;
	};

	class Tree
	{
	public:
		Tree(Map map, const ID id, const int maxDepth);
		Column GetMaxScoreColumn();
	private:
		Score AlphaBetaPruning(Node* node, int depth, Score alpha, Score beta, bool isMaximizingPlayer);
		Score NegaMax(Node* node, int depth, Score alpha, Score beta);

	private:
		Node root;
		Node* bestNode;
		ID id;
		int maxDepth;
		Map map;
	};

};

#endif
