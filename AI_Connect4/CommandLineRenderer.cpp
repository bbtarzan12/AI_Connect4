#include "CommandLineRenderer.h"
#include "Game.h"
#include <iostream>
#include "Map.h"

using namespace std;

void CommandlineRenderer::Render(const std::shared_ptr<Game>& game) const
{
	Map& map = game->GetGameMap();

	for (Row row = MAX_ROW - 1; row >= 0; row--)
	{
		for (Column column = 0; column < MAX_COLUMN; column++)
		{
			const ID& id = map[column][row];

			if (id == EMPTY_ID)
				cout << "   ";
			else
				cout << " " << id << " ";

			cout << "¦¢";
		}
		cout << endl;
	}
	cout << endl;
}
