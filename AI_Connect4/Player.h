#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <memory>

#include "Type.h"
#include "Controller.h"

class Game;

class Player : public std::enable_shared_from_this<Player>
{
	friend std::ostream& operator <<(std::ostream& stream, const Player& player)
	{
		stream << "Player(" << player.name << ")";
		return stream;
	}

public:
	template<typename T>
	static std::shared_ptr<Player> Create(ID id, std::string name, const std::shared_ptr<Game>& game)
	{
		std::shared_ptr<Player> player = std::make_shared<Player>(Player(id, name, game));
		std::shared_ptr<Controller> controller = std::make_shared<T>(player);
		player->SetController(controller);
		return player;
	}

	Column GetPlayerInput();

	const Map& GetGameMap() const;
	const ID& GetPlayerID() const;

private:
	Player(ID id, std::string name, const std::shared_ptr<Game>& game);
	void SetController(std::shared_ptr<Controller>& controller);

private:
	ID id;
	std::string name;
	std::shared_ptr<Game> game;
	std::shared_ptr<Controller> controller;
};

#endif