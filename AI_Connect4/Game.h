#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include <memory>
#include "Controller.h"

class Player;

class Game
{

public:
	void Initialize();
	void AddPlayer(const std::string& name, const Controller::Type type);
	void Update();
	void Release();

	Map* GetGameMap();

	bool isGameFinished();

private:
	Map* map;

	std::vector<std::shared_ptr<Player>> players;
	ID numPlayer;

};

#endif
