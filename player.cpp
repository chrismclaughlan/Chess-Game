#include "types.h"
#include "player.h"
#include "board.h"

Player::Player
(Board* parent, int32 mask[], int32 width, int32 height, const uint32 colour)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile* ntile = parent->getTile(x + (width * y));

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