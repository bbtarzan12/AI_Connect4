#include "Game.h"
#include "Player.h"
#include <iostream>

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

	if (isGameEnd = CheckGameEndBy4Connected(coord, player->GetPlayerID()) || map.IsMapFull())
	{
		cout << "Game End!!" << endl;
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

bool Game::CheckGameEndBy4Connected(const Coord& coord, const ID& id)
{
	const Column& column = coord.first;
	const Row& row = coord.second;

	for (int neighborColumn = column - 1; neighborColumn <= column + 1; neighborColumn++)
	{
		for (int neighborRow = row - 1; neighborRow <= row; neighborRow++)
		{
			if(!CheckCoordIsInBound(neighborColumn, neighborRow))
				continue;

			if(neighborColumn == column && neighborRow == row)
				continue;

			int deltaColumn = neighborColumn - column;
			int deltaRow = neighborRow - row;
			int numOfNeighbor = GetNumOfNeighbor(coord, deltaColumn, deltaRow, id) + GetNumOfNeighbor(coord, -deltaColumn, -deltaRow, id) + 1;
			if (numOfNeighbor >= 4)
				return true;
		}
	}

	return false;
}

int Game::GetNumOfNeighbor(const Coord& originCoord, const int& deltaColumn, const int& deltaRow, const ID& id)
{
	Coord neighborCoord = Coord(originCoord.first + deltaColumn, originCoord.second + deltaRow);
	const Column& neighborColumn = neighborCoord.first;
	const Row& neighborRow = neighborCoord.second;
	
	if (!CheckCoordIsInBound(neighborColumn, neighborRow))
		return 0;

	if (map[neighborColumn][neighborRow] == id)
		return GetNumOfNeighbor(neighborCoord, deltaColumn, deltaRow, id) + 1;

	return 0;
}

bool Game::CheckCoordIsInBound(const Column& column, const Row& row)
{
	if (column >= MAX_COLUMN || column < 0)
		return false;

	if (row >= MAX_ROW || row < 0)
		return false;

	return true;
}