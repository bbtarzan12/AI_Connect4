#ifndef H_RENDERER
#define H_RENDERER
#include <memory>

class Game;

class Renderer
{
	
public:
	enum class Type { COMMAND };
	static std::unique_ptr<Renderer> MakeRenderer(Type type);


public:
	virtual void Render(const std::shared_ptr<Game>& game) const = 0;

};

#endif
