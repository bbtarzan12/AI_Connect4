#include "Game.h"
#include "Player.h"
#include <iostream>

using namespace std;

void Game::Initialize()
{
	numPlayer = 0;
	isGameEnd = false;

	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		for (Row row = 0; row < MAX_ROW; row++)
		{
			map[column][row] = EMPTY_ID;
		}
	}
}

void Game::AddPlayer(const string& name, const Controller::Type type)
{
	shared_ptr<Player> newPlayer = make_shared<Player>(numPlayer, name, type);
	numPlayer++;

	players.push_back(newPlayer);
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
		coord = GetCoordFromMap(column, isValidCoord);

		if (!isValidCoord)
		{
			cout << "There is no space. Try Again" << endl;
		}
	}

	SetCoordToMap(player, coord);

	if (isGameEnd = CheckGameEndBy4Connected(coord, player->GetPlayerID()) || CheckMapIsFull())
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


const Map& Game::GetGameMap() const
{
	return map;
}

bool Game::isGameFinished()
{
	return isGameEnd;
}

Coord Game::GetCoordFromMap(const Column& column, bool& isValid)
{
	for (Row row = 0; row < MAX_ROW; row++)
	{
		if (map[column][row] != EMPTY_ID)
			continue;

		isValid = true;
		return Coord(column, row);
	}

	isValid = false;
	return Coord();
}

void Game::SetCoordToMap(const shared_ptr<Player>& player, const Coord& coord)
{
	map[coord.first][coord.second] = player->GetPlayerID();
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

bool Game::CheckMapIsFull()
{
	for (Column column = 0; column < MAX_COLUMN; column++)
	{
		for (Row row = 0; row < MAX_ROW; row++)
		{
			if (map[column][row] == EMPTY_ID)
				return false;
		}
	}
	return true;
}
