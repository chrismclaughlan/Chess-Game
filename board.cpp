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
	PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
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

	current_tile = tiles.begin();

	players.push_back(new Player(this, player1_mask, 8, 8, WHITE));
	players.push_back(new Player(this, player2_mask, 8, 8, BLACK));

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

		// Draw selected tile
		Tile* tile = *current_tile;
		if (tiles[i] == tile)
		{
			tiles[i]->drawOutline(width, height, 0x00ad43, 0.7);
		}
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
		players[i]->draw(width, height);
}

void Board::selectUp()
{
	// if hit top boundary; warp to bottom
	if ((current_tile - tiles.begin()) + width > width * height)
	{
		std::advance(current_tile, -(width * (height - 1)));
	}
	else
	{
		std::advance(current_tile, width);
	}
}

void Board::selectDown()
{
	// if hit bottom boundary; warp to top
	if ((current_tile - tiles.begin()) - width < 0)
	{
		std::advance(current_tile, +(width * (height - 1)));
	}
	else
	{
		std::advance(current_tile, -width);
	}
}

void Board::selectLeft()
{
	// if hit left boundary; warp to right

	if ((current_tile - tiles.begin()) % width == 0)
	{
		std::advance(current_tile, width - 1);
	}
	else
	{
		std::advance(current_tile, -1);
	}
}

void Board::selectRight()
{
	// if hit right boundary; warp to other side
	if ((current_tile - tiles.begin() + 1) % width == 0)
	{
		std::advance(current_tile, -(width - 1));
	}
	else
	{
		std::advance(current_tile, 1);
	}
}

void Board::selectEnter()
{

}

void Board::selectCancel()
{

}