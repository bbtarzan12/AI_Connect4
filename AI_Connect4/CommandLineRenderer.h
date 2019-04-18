#ifndef H_COMMANDLINERENDERER
#define H_COMMANDLINERENDERER
#include "Renderer.h"

class CommandlineRenderer : public Renderer
{

public:

	virtual void Render(const Game& game) const override;

};

#endif