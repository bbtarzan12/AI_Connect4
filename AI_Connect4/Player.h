#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <memory>

#include "Type.h"
#include "Controller.h"

enum class Controller::Type;

class Player
{
	friend std::ostream& operator <<(std::ostream& stream, const Player& player)
	{
		stream << "Player(" << player.name << ")";
		return stream;
	}

public:
	Player(ID id, std::string name, const Controller::Type type);
	Column GetPlayerInput();
	const ID& GetPlayerID() const;

private:
	ID id;
	std::string name;

	std::shared_ptr<Controller> controller;
};

#endif
