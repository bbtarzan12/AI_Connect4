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

	const Map& GetGameMap() const;

	bool isGameFinished();

private:
	Game() = default;
	Coord GetCoordFromMap(const Column& column, bool& isValid);
	void SetCoordToMap(const std::shared_ptr<Player>& player, const Coord& coord);
	bool CheckGameEndBy4Connected(const Coord& coord, const ID& id);
	int GetNumOfNeighbor(const Coord& originCoord, const int& deltaColumn, const int& deltaRow, const ID& id);
	bool CheckCoordIsInBound(const Column& column, const Row& row);
	bool CheckMapIsFull();

private:
	Map map;

	std::vector<std::shared_ptr<Player>> players;
	ID currentTurnPlayerID;
	int numPlayer;
	bool isGameEnd;

};

#endif
