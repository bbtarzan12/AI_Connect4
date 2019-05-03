#include "AIMCTSController.h"
#include <algorithm>
#include <iostream>
#include "Player.h"
#include "Random.h"
#include "CommandLineRenderer.h"

using namespace std;

AIMCTSController::AIMCTSController(const std::shared_ptr<Player>& player)
{
	this->player = player;
}

Column AIMCTSController::GetPlayerInput()
{
	// MCTS 
	const ID id = player->GetPlayerID();
	Map& map = player->GetGameMap();
	Node root = Node(id, nullptr);
	root.map = map;

	for (int numSimulation = 1; numSimulation <= 10000; numSimulation++)
	{
		// Selection
		Node* selectedNode = Selection(&root);

		// Expansion
		Node* expandedNode = Expansion(selectedNode);

		if(expandedNode == nullptr)
			continue;

		// Simulation
		int totalSimulation = 0;
		int totalWin = 0;
		Simulation(expandedNode, 1000, totalSimulation, totalWin);

		// Backpropagation
		Backpropagation(expandedNode, expandedNode->id, totalSimulation, totalWin);

	}
	cout << "Root Simulation : " << root.simulations << " Win : " << root.wins << endl;
	for (auto & child : root.childs)
	{
		cout << "Child Simulation : " << child->simulations << " Win : " << child->wins << " UCT : " << child->UCT() << endl;
	}
	//Column maxColumn = distance(root.childs.begin(), max_element(root.childs.begin(), root.childs.end(), [](const Node* l, const Node* r) { return l->UCT() < r->UCT(); }));

	return (*max_element(root.childs.begin(), root.childs.end(), [](const Node* l, const Node* r) { return l->UCT() < r->UCT(); }))->column;
}

AIMCTSController::Node* AIMCTSController::Selection(Node* node)
{
	if (node->childs.empty())
		return node;

	Node* maxUCTChild = *max_element(node->childs.begin(), node->childs.end(), [](const Node* l, const Node* r) { return l->UCT() < r->UCT(); });
	return Selection(maxUCTChild);
}

AIMCTSController::Node* AIMCTSController::Expansion(Node* node)
{
	for (Column column = 0; column < MAX_COLUMN; column++)
	{

		bool isvalid = false;
		Coord coord = node->map.GetEmptyCoord(column, isvalid);
		if (!isvalid)
		{
			continue;
		}

		const ID childID = node->id ^ 1;
		Node* child = new Node(childID, node);
		child->map = node->map;
		child->map.SetCoord(childID, coord);
		child->column = column;

		node->childs.push_back(child);
	}

	if (node->childs.empty())
		return nullptr;

	return node->childs.at(RandomGenerator<XOR128>::Random(0, node->childs.size() - 1));
}

void AIMCTSController::Simulation(Node* node, int maxSimulation, int& totalSimulation, int& totalWin)
{

	for (totalSimulation = 1; totalSimulation <= maxSimulation; totalSimulation++)
	{
		ID currentID = node->id;
		Map map = node->map;
		Coord lastMove = map.lastMove;

		while (!(map.IsGameEnd(lastMove, currentID) || map.IsMapFull()))
		{
			currentID = currentID ^ 1;
			Column validColumns[MAX_COLUMN];
			int numOfValidColumns = 0;

			for (Column column = 0; column < MAX_COLUMN; column++)
			{
				if (!map.IsColumnValid(column))
					continue;

				validColumns[numOfValidColumns++] = column;
			}

			if (numOfValidColumns == 0)
			{
				cout << "Un Error Occured 1" << endl;
				CommandlineRenderer::Dump(map);
				return;
			}

			int randomIndex = RandomGenerator<XOR128>::Random(0, numOfValidColumns - 1);
			if (randomIndex >= numOfValidColumns)
			{
				cout << "randomIndex >= numOfValidColumns" << endl;
				return;
			}

			Column randomColumn = validColumns[randomIndex];

			bool isValid = false;
			Coord randomCoord = map.GetEmptyCoord(randomColumn, isValid);
			if (!isValid)
			{
				cout << "Un Error Occured Coord : " << randomCoord.first << ", " << randomCoord.second << endl;
				CommandlineRenderer::Dump(map);
				return;
			}

			map.SetCoord(currentID, randomCoord);
			lastMove = randomCoord;
		}

		if (map.winID != EMPTY_ID && map.winID != node->id) // ex) 노드가 id 1 인데 승리한 id가 0이면 win++
		{
			totalWin++;
		}
	}

}

void AIMCTSController::Backpropagation(Node* node, const ID winID, const int totalSimulation, const int totalWin)
{
	if (node == nullptr)
		return;

	node->simulations += totalSimulation;
	if (node->id != winID && node->id != EMPTY_ID)
		node->wins += totalWin;
	else if (node->id == winID && node->id != EMPTY_ID)
		node->wins += (totalSimulation - totalWin);

	Backpropagation(node->parent, winID, totalSimulation, totalWin);
}

const float AIMCTSController::Node::UCT() const
{
	if (parent == nullptr)
		return -1;
	float exploitation = (float) wins / (simulations + 1);
	float exploration = EXPLORATION_PARAMETER * sqrt(log(parent->simulations) / (float)(simulations + 1));
	return exploitation + exploration;
}
