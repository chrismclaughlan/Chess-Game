#include "types.h"
#include "player.h"
#include "board.h"

Player::Player
(Board* nparent, int32 mask[], int32 width, int32 height, const uint32 colour, const uint32 nselection_colour)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile* ntile = nparent->getTile(x + (width * y));

			if (mask[x + (y * width)] == PAWN)
			{
				pawns.push_back(new Pawn(ntile));
				//pawns.push_back(new Pawn(ntile, colour));
			}
			if (mask[x + (y * width)] == ROOK)
			{
				rooks.push_back(new Rook(ntile));
				//rooks.push_back(new Rook(ntile, colour));
			}
			if (mask[x + (y * width)] == KNIG)
			{
				knights.push_back(new Knight(ntile));
				//knights.push_back(new Knight(ntile, colour));
			}
			if (mask[x + (y * width)] == BISH)
			{
				bishops.push_back(new Bishop(ntile));
				//bishops.push_back(new Bishop(ntile, colour));
			}
			if (mask[x + (y * width)] == QUEE)
			{
				queens.push_back(new Queen(ntile));
				//queens.push_back(new Queen(ntile, colour));
			}
			if (mask[x + (y * width)] == KING)
			{
				kings.push_back(new King(ntile));
				//kings.push_back(new King(ntile, colour));
			}
		}
	}

	std::vector<Tile*>* tiles = nparent->getTiles();
	current_tile = tiles->begin();
	parent = nparent;
	selection_colour = nselection_colour;
}

Player::~Player()
{
	pawns.clear();
	rooks.clear();
	knights.clear();
	bishops.clear();
	queens.clear();
	kings.clear();
}

void Player::draw(int32 width, int32 height)
{
	for (std::vector<Pawn>::size_type i = 0; i != pawns.size(); i++)
		pawns[i]->draw(width, height);
	for (std::vector<Rook>::size_type i = 0; i != rooks.size(); i++)
		rooks[i]->draw(width, height);
	for (std::vector<Knight>::size_type i = 0; i != knights.size(); i++)
		knights[i]->draw(width, height);
	for (std::vector<Bishop>::size_type i = 0; i != bishops.size(); i++)
		bishops[i]->draw(width, height);
	for (std::vector<Queen>::size_type i = 0; i != queens.size(); i++)
		queens[i]->draw(width, height);
	for (std::vector<King>::size_type i = 0; i != kings.size(); i++)
		kings[i]->draw(width, height);
}

void Player::drawSelection(int32 width, int32 height)
{
	// Draw selected tile
	std::vector<Tile*>* tiles = parent->getTiles();
	std::vector<Tile*> _tiles = *tiles;
	Tile* ct = *current_tile;
	for (std::vector<Tile>::size_type i = 0; i != tiles->size(); i++)
	{
		if (_tiles[i] == ct)
		{
			_tiles[i]->drawOutline(width, height, selection_colour, 0.7);
		}
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

void Player::selectEnter()
{
	std::vector<Tile*>* tiles = parent->getTiles();
	std::vector<Tile*> _tiles = *tiles;
	Tile* ct = *current_tile;

#define selectPieces(a, b, c)\
{\
for (std::vector<a>::size_type i = 0; i != b.size(); i++)\
{\
if (b[i]->getPosition() == c)\
{\
if (b[i]->isSelected())\
{\
b[i]->deSelect(); \
}\
else\
{\
b[i]->select();\
}\
}\
}\
}\

	selectPieces(Pawn, pawns, ct);
	selectPieces(Rook, rooks, ct);
	selectPieces(Knight, knights, ct);
	selectPieces(Bishop, bishops, ct);
	selectPieces(Queen, queens, ct);
	selectPieces(King, kings, ct);

	//for (std::vector<Pawn>::size_type i = 0; i != pawns.size(); i++)
	//	selectPiece(pawns, ct);
	//for (std::vector<Rook>::size_type i = 0; i != rooks.size(); i++)
	//	selectPiece(rooks, ct);
	//for (std::vector<Knight>::size_type i = 0; i != knights.size(); i++)
	//	selectPiece(knights, ct);
	//for (std::vector<Bishop>::size_type i = 0; i != bishops.size(); i++)
	//	selectPiece(bishops, ct);
	//for (std::vector<Queen>::size_type i = 0; i != queens.size(); i++)
	//	selectPiece(queens, ct);
	//for (std::vector<King>::size_type i = 0; i != kings.size(); i++)
	//	selectPiece(kings, ct);
}

void Player::selectCancel()
{
	//std::vector<Tile*>* tiles = parent->getTiles();
	//std::vector<Tile*> _tiles = *tiles;

	//for (std::vector<Tile>::size_type i = 0; i != _tiles.size(); i++)
	//	_tiles[i]->deSelect();

#define deSelectPieces(a, b)\
for (std::vector<a>::size_type i = 0; i != b.size(); i++)\
{\
	b[i]->deSelect();\
}\

	deSelectPieces(Pawn, pawns);
	deSelectPieces(Rook, rooks);
	deSelectPieces(Knight, knights);
	deSelectPieces(Bishop, bishops);
	deSelectPieces(Queen, queens);
	deSelectPieces(King, kings);
	// remove selection from all tiles
	//for (std::vector<Pawn>::size_type i = 0; i != pawns.size(); i++)
	//{
	//	pawns[i]->deSelect();
	//}
	//for (std::vector<Rook>::size_type i = 0; i != rooks.size(); i++)
	//	rooks[i]->deSelect();
	//for (std::vector<Knight>::size_type i = 0; i != knights.size(); i++)
	//	knights[i]->deSelect();
	//for (std::vector<Bishop>::size_type i = 0; i != bishops.size(); i++)
	//	bishops[i]->deSelect();
	//for (std::vector<Queen>::size_type i = 0; i != queens.size(); i++)
	//	queens[i]->deSelect();
	//for (std::vector<King>::size_type i = 0; i != kings.size(); i++)
	//	kings[i]->deSelect();
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