#ifndef H_COMMANDLINERENDERER
#define H_COMMANDLINERENDERER
#include "Renderer.h"
#include <memory>

class CommandlineRenderer : public Renderer
{

public:

	virtual void Render(const std::shared_ptr<Game>& game) const override;

};

#endif