#include "types.h"
#include "player.h"
#include "board.h"

Player::Player
(Board* nparent, int32 mask[], int32 width, int32 height, const uint32 colour, const uint32 ncursor_colour)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile* ntile = nparent->getTile(x + (width * y));

			if (mask[x + (y * width)] == PAWN)
			{
				Pawn* npiece = new Pawn(ntile);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == ROOK)
			{
				Rook* npiece = new Rook(ntile);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == KNIG)
			{
				Knight* npiece = new Knight(ntile);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == BISH)
			{
				Bishop* npiece = new Bishop(ntile);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == QUEE)
			{
				Queen* npiece = new Queen(ntile);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == KING)
			{
				King* npiece = new King(ntile);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
		}
	}

	std::vector<Tile*>* tiles = nparent->getTiles();
	current_tile = tiles->begin();
	parent = nparent;
	cursor_colour = ncursor_colour;
}

Player::~Player()
{
	pieces.clear();
}

void Player::draw(int32 width, int32 height)
{
	for (std::vector<Piece*>::size_type i = 0; i != pieces.size(); i++)
		pieces[i]->draw(width, height);
}

void Player::drawCursor(int32 width, int32 height)
{
	// Draw selected tile
	std::vector<Tile*>* tiles = parent->getTiles();
	std::vector<Tile*> _tiles = *tiles;
	Tile* ct = *current_tile;
	for (std::vector<Tile>::size_type i = 0; i != tiles->size(); i++)
	{
		if (_tiles[i] == ct)
		{
			_tiles[i]->drawOutline(width, height, cursor_colour, .5);
		}
	}
}

void Player::drawSelection(int32 width, int32 height)
{
	// Draw selected tile

	for (std::vector<Tile>::size_type i = 0; i != selected_tiles.size(); i++)
	{
		selected_tiles[i]->drawOutline(width, height, selection_colour, 1);
	}
}

void Player::selectUp()
{
	// if hit top boundary; warp to bottom
	std::vector<Tile*>* tiles = parent->getTiles();
	int32 width = parent->getWidth();
	int32 height = parent->getHeight();
	if ((current_tile - tiles->begin()) + width > width * height)
	{
		std::advance(current_tile, -(width * (height - 1)));
	}
	else
	{
		std::advance(current_tile, width);
	}
}

void Player::selectDown()
{
	// if hit bottom boundary; warp to top
	std::vector<Tile*>* tiles = parent->getTiles();
	int32 width = parent->getWidth();
	int32 height = parent->getHeight();
	if ((current_tile - tiles->begin()) - width < 0)
	{
		std::advance(current_tile, +(width * (height - 1)));
	}
	else
	{
		std::advance(current_tile, -width);
	}
}

void Player::selectLeft()
{
	// if hit left boundary; warp to right
	std::vector<Tile*>* tiles = parent->getTiles();
	int32 width = parent->getWidth();
	if ((current_tile - tiles->begin()) % width == 0)
	{
		std::advance(current_tile, width - 1);
	}
	else
	{
		std::advance(current_tile, -1);
	}
}

void Player::selectRight()
{
	// if hit right boundary; warp to other side
	std::vector<Tile*>* tiles = parent->getTiles();
	int32 width = parent->getWidth();
	if ((current_tile - tiles->begin() + 1) % width == 0)
	{
		std::advance(current_tile, -(width - 1));
	}
	else
	{
		std::advance(current_tile, 1);
	}
}

void Player::select()
{
	Tile* ct = *current_tile;
	int32 size = selected_tiles.size();
	if (size == 0)
		selected_tiles.push_back(ct);
	else if (size == 1)
	{
		if (selected_tiles[0] == ct)
			selected_tiles.clear();
		else
			selected_tiles.push_back(ct);
	}
	else if (size == 2)
	{
		if (selected_tiles[0] == ct)
			selected_tiles.clear();
		else if (selected_tiles[1] == ct)
			selected_tiles.pop_back();
	}
}

void Player::selectCancel()
{
	if (selected_tiles.empty())
		return;

	selected_tiles.pop_back();
}

void Player::selectClear()
{
	selected_tiles.clear();
}

void Player::checkTile(Tile* ntile)
{
	//for (std::vector<Pawn>::size_type i = 0; i != pawns.size(); i++)
	//{
	//	if (pawns[i]->getPosition() == ntile)
	//	{
	//		pawns[i]->select();
	//	}
	//}
	//for (std::vector<Rook>::size_type i = 0; i != rooks.size(); i++)
	//{
	//}
	//	rooks[i]->
	//for (std::vector<Knight>::size_type i = 0; i != knights.size(); i++)
	//	knights[i]->
	//for (std::vector<Bishop>::size_type i = 0; i != bishops.size(); i++)
	//	bishops[i]->
	//for (std::vector<Queen>::size_type i = 0; i != queens.size(); i++)
	//	queens[i]->
	//for (std::vector<King>::size_type i = 0; i != kings.size(); i++)
	//	kings[i]->
}