#include "Game.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

using namespace std;

std::shared_ptr<Game> Game::Create()
{
	return std::make_shared<Game>(Game());
}

void Game::Initialize()
{
	numPlayer = 0;
	isGameEnd = false;
}

void Game::Update()
{
	const shared_ptr<Player>& player = players.at(currentTurnPlayerID);
	cout << *player << " Turn" << endl;

	bool isValidCoord = false;
	Coord coord;

	while (!isValidCoord)
	{
		const Column& column = player->GetPlayerInput();
		coord = map.GetEmptyCoord(column, isValidCoord);

		if (!isValidCoord)
		{
			cout << "There is no space. Try Again" << endl;
		}
	}

	map.SetCoord(player->GetPlayerID(), coord);

	if (isGameEnd = map.IsGameEnd(coord, player->GetPlayerID()) || map.IsMapFull())
	{
		cout << "Game End!!" << endl;
		if (map.winID == EMPTY_ID)
		{
			cout << "Draw!!" << endl;
		}
		else
		{
			cout << *players.at(map.winID) << " win!!" << endl;
		}
	}

	currentTurnPlayerID++;
	if (currentTurnPlayerID >= players.size())
	{
		currentTurnPlayerID = 0;
	}
}

void Game::Release()
{
	for (auto & player : players)
	{
	}
}


Map& Game::GetGameMap()
{
	return map;
}

bool Game::isGameFinished()
{
	return isGameEnd;
}