#ifndef H_AIPUREMCTSCUDACONTROLLER
#define H_AIPUREMCTSCUDACONTROLLER

#include "Type.h"
#include "Controller.h"
#include "Map.h"

class AIPureMCTSCudaController : public Controller
{
public:
	AIPureMCTSCudaController(const std::shared_ptr<Player>& player);

	virtual Column GetPlayerInput() override;

};


#endif


