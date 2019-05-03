#ifndef H_AIMCTSCONTROLLER
#define H_AIMCTSCONTROLLER

#include "Type.h"
#include "Controller.h"
#include <vector>
#include "Map.h"

constexpr float EXPLORATION_PARAMETER = 1.41421356237f; // sqrt(2)

class AIMCTSController : public Controller
{

public:
	AIMCTSController(const std::shared_ptr<Player>& player);
	virtual Column GetPlayerInput() override;
		

private:
	struct Node
	{
		Node(ID id, Node* parent) : id(id), parent(parent) {}
		~Node()
		{
			for (auto & child : childs)
			{
				delete child;
			}
			childs.clear();
		}
		ID id;
		int wins = 0;
		int simulations = 0;
		Column column;
		Node* parent = nullptr;
		Map map;
		std::vector<Node*> childs;

		const float UCT() const;
	};

	Node* Selection(Node* node);
	Node* Expansion(Node* node);
	void Simulation(Node* node, int maxSimulation, int& totalSimulation, int& totalWin);
	void Backpropagation(Node* node, const ID winID, const int totalSimulation, const int totalWin);
};

#endif
