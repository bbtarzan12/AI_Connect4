#ifndef H_RENDERER
#define H_RENDERER

class Game;

class Renderer
{

public:
	virtual void Render(const Game& game) const = 0;

};

#endif
