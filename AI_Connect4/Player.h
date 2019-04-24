#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <memory>

#include "Type.h"
#include "Controller.h"

class Game;

enum class Controller::Type;

class Player : public std::enable_shared_from_this<Player>
{
	friend std::ostream& operator <<(std::ostream& stream, const Player& player)
	{
		stream << "Player(" << player.name << ")";
		return stream;
	}

public:
	static std::shared_ptr<Player> Create(ID id, std::string name, const Controller::Type type, const std::shared_ptr<Game>& game);

	Column GetPlayerInput();

	const Map& GetGameMap() const;
	const ID& GetPlayerID() const;

private:
	Player(ID id, std::string name, const Controller::Type type, const std::shared_ptr<Game>& game);
	void AddController(const Controller::Type type);

private:
	ID id;
	std::string name;
	std::shared_ptr<Game> game;
	std::shared_ptr<Controller> controller;
};

#endif
