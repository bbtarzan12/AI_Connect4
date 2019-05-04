#ifndef H_AIPUREMCTSCONTROLLER
#define H_AIPUREMCTSCONTROLLER

#include "Type.h"
#include "Controller.h"
#include "Map.h"

class AIPureMCTSController : public Controller
{
public:
	AIPureMCTSController(const std::shared_ptr<Player>& player);

	virtual Column GetPlayerInput() override;

	void Simulation(Map& childMap, int maxSimulation, int& numSimulation, int& totalWin);
};


#endif


