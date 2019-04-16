#include "Game.h"
#include "Player.h"
#include <iostream>

using namespace std;

void Game::Initialize()
{
	map = new Map;
	numPlayer = 0;
}

void Game::AddPlayer(const string& name, const Controller::Type type)
{
	shared_ptr<Player> newPlayer = make_shared<Player>(numPlayer, name, type);
	numPlayer++;

	players.push_back(newPlayer);
}

void Game::Update()
{
	for (auto & player : players)
	{
		Coord coord = player->GetPlayerInput();
		cout << *player << " " << coord.first << " " << coord.second << endl;
	}
}

void Game::Release()
{
	
}



Map* Game::GetGameMap()
{
	return map;
}

bool Game::isGameFinished()
{
	return false;
}
