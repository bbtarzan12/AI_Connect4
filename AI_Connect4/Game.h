#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include <memory>
#include "Controller.h"
#include "Player.h"

class Game : public std::enable_shared_from_this<Game>
{

public:
	static std::shared_ptr<Game> Create();

	void Initialize();

	template<typename T>
	void AddPlayer(const std::string& name)
	{
		std::shared_ptr<Player> newPlayer = Player::Create<T>(numPlayer, name, shared_from_this());
		numPlayer++;

		players.push_back(newPlayer);
	}

	void Update();
	void Release();

	Map& GetGameMap();

	bool isGameFinished();

private:
	Game() = default;

private:
	Map map;

	std::vector<std::shared_ptr<Player>> players;
	ID currentTurnPlayerID;
	int numPlayer;
	bool isGameEnd;

};

#endif
