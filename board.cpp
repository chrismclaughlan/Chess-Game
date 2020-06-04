#include <stdlib.h>
#include <vector>
#include "game.h"
#include "board.h"
#include "render.h"
#include "pieces.h"

extern RenderState rs;

int32 player1_mask[64] =
{
	ROOK, KNIG, BISH, KING, QUEE, BISH, KNIG, ROOK,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
};

int32 player2_mask[64] =
{
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT, EMPT,
	PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
	ROOK, KNIG, BISH, QUEE, KING, BISH, KNIG, ROOK,
};

Board::Board()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile* ntile = new Tile(x, y);

			// Create tile checker-board pattern
			if (y % 2 == 0)
			{
				if (x % 2 == 0)
					ntile->setColour(BEIGE);
				else
					ntile->setColour(BROWN);
			}
			else
			{
				if (x % 2 == 0)
					ntile->setColour(BROWN);
				else
					ntile->setColour(BEIGE);
			}

			tiles.push_back(ntile);
		}
	}

	//current_tile = tiles.begin();

	players.push_back(new Player(this, player1_mask, 8, 8, WHITE, RED, false));
	players.push_back(new Player(this, player2_mask, 8, 8, BLACK, BLUE, true));

	current_player = players.begin();
}

Board::Board(const Board& prev)
{
	this->width = prev.width;
	this->height = prev.height;

	this->tiles = prev.tiles;
	this->players = prev.players;

	// iterator turn to next player
	if (prev.current_player < prev.players.end())
	{
		this->current_player = prev.current_player;
		std::advance(this->current_player, 1);
	}
	else
	{
		this->current_player = players.begin();
	}
}

Board::~Board()
{
	tiles.clear();
	players.clear();
}

void Board::drawTiles()
{
	for (std::vector<Tile>::size_type i = 0; i != tiles.size(); i++)
	{
		tiles[i]->draw(width, height);
	}
}

void Board::drawOutlines()
{
	for (std::vector<Tile>::size_type i = 0; i != tiles.size(); i++)
	{
		tiles[i]->drawOutline(width, height, 0xff0000, 0.2);
	}
}

void Board::drawPlayers()
{
	for (std::vector<Player>::size_type i = 0; i != players.size(); i++)
	{
		players[i]->draw(width, height);
	}
}

void Board::drawPlayerCursor()
{
	Player* cp = *current_player;
	cp->drawCursor(width, height);
}

void Board::drawPlayerSelection()
{
	Player* cp = *current_player;
	cp->drawSelection(width, height);
}

void Board::nextPlayer()
{
	std::advance(current_player, 1);

	if (current_player == players.end())
	{
		current_player = players.begin();
	}
}