#include <vector>
#include "types.h"
#include "player.h"
#include "board.h"

Player::Player
(Board* nparent, int32 mask[], int32 width, int32 height, const uint32 ncolour, const uint32 ncursor_colour, bool nreverse)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile* ntile = nparent->getTile(x + (width * y));

			if (mask[x + (y * width)] == PAWN)
			{
				Pawn* npiece = new Pawn(ntile, ncolour);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == ROOK)
			{
				Rook* npiece = new Rook(ntile, ncolour);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == KNIG)
			{
				Knight* npiece = new Knight(ntile, ncolour);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == BISH)
			{
				Bishop* npiece = new Bishop(ntile, ncolour);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == QUEE)
			{
				Queen* npiece = new Queen(ntile, ncolour);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
			if (mask[x + (y * width)] == KING)
			{
				King* npiece = new King(ntile, ncolour);
				pieces.push_back(npiece);
				ntile->setPiece(npiece);
			}
		}
	}

	std::vector<Tile*>* tiles = nparent->getTiles();
	current_tile = tiles->begin();
	parent = nparent;
	cursor_colour = ncursor_colour;
	colour = ncolour;
	reverse = nreverse;
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
	std::vector<Tile*>* _tiles = parent->getTiles();
	std::vector<Tile*> tiles = *_tiles;
	Tile* ct = *current_tile;
	for (std::vector<Tile>::size_type i = 0; i != tiles.size(); i++)
	{
		if (tiles[i] == ct)
		{
			tiles[i]->drawOutline(width, height, cursor_colour, .5);
		}
	}
}

void Player::drawSelection(int32 width, int32 height)
{
	for (std::vector<Tile>::size_type i = 0; i != selected_tiles.size(); i++)
	{
		selected_tiles[i]->drawOutline(width, height, selection_colour, 1);
	}
}

void Player::selectUp()
{
	// if hit top boundary; warp to bottom
	std::vector<Tile*>* tiles = parent->getTiles();
	//std::vector<Tile*> tiles = *_tiles;
	int32 width = parent->getWidth();
	int32 height = parent->getHeight();
	if ((current_tile - tiles->begin()) + width >= width * height)
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
	//std::vector<Tile*> tiles = *_tiles;
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
	//std::vector<Tile*> tiles = *_tiles;
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
	//std::vector<Tile*> tiles = *_tiles;
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
	if (size == 0)  // SELECTION EMPTY
	{
		Piece* piece = ct->getPiece();
		if (piece)
		{
			if (piece->getColour() == colour)
			{
				selected_tiles.push_back(ct);  // if my peice -> select
				this->calculatePossibleMoves();
			}
		}
		else
		{
			return;
		}
	}
	else if (size == 1)  // PIECE ALREADY SELECTED
	{
		if (selected_tiles[0] == ct)
		{
			selected_tiles.clear();
			this->clearPossibleMoves();
		}
		else if (ct->isPossibleMove())
		{
			selected_tiles.push_back(ct);
		}
	}
	else if (size == 2)  // PIECE AND TILE ALREADY SELECTED
	{
		if (selected_tiles[0] == ct)  // if piece; clear
		{
			selected_tiles.clear();
			this->clearPossibleMoves();
		}
		else if (selected_tiles[1] == ct)  // if tile; clear
			selected_tiles.pop_back();
		else if (ct->isPossibleMove())  // if possible move; switch tiles
		{
			selected_tiles.pop_back();
			selected_tiles.push_back(ct);
		}
	}
}

void Player::selectCancel()
{
	if (selected_tiles.empty())
		return;
	else if (selected_tiles.size() == 1)
		this->clearPossibleMoves();

	selected_tiles.pop_back();
}

void Player::selectClear()
{
	selected_tiles.clear();
	this->clearPossibleMoves();
}

void Player::calculatePossibleMoves()
{
	if (selected_tiles.size() == 1)
	{
		Piece* piece = selected_tiles[0]->getPiece();
		std::vector<Tile*>* tiles = parent->getTiles();
		int32 current_idx = current_tile - tiles->begin();
		piece->fillPossibleMoves(*tiles, current_idx, this);
	}
}

void Player::clearPossibleMoves()
{
	// reset possible moves
	std::vector<Tile*>* tiles = parent->getTiles();
	std::vector<Tile*> _tiles = *tiles;
	for (std::vector<Tile>::size_type i = 0; i != tiles->size(); i++)
	{
		_tiles[i]->setPossibleMove(false);
	}
}

bool Player::hasPiece(Piece* piece)
{
	for (std::vector<Piece>::size_type i = 0; i != pieces.size(); i++)
	{
		if (pieces[i] == piece)
			return true;
	}
	return false;
}

bool Player::validateTurn()
{
	if (selected_tiles.size() != 2)
		return false;

	// move piece
	Tile* tile_from = selected_tiles[0];
	Tile* tile_to = selected_tiles[1];
	Piece* piece_to_move = tile_from->getPiece();
	Piece* piece_to_replace = tile_to->getPiece();

	if (piece_to_replace)
	{
		piece_to_replace->~Piece();
	}

	tile_from->setPiece(nullptr);
	tile_to->setPiece(piece_to_move);
	piece_to_move->setPosition(tile_to);
	return true;
}