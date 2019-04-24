#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include <memory>
#include "Controller.h"

class Player;

class Game : public std::enable_shared_from_this<Game>
{

public:
	static std::shared_ptr<Game> Create();

	void Initialize();
	void AddPlayer(const std::string& name, const Controller::Type type);
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
