#include <stdlib.h>
#include <vector>
#include "game.h"
#include "board.h"
#include "render.h"
#include "pieces.h"

extern RenderState rs;

//static int32 player1_pawn_mask[8][8] =
static uint32 player1_piece_mask[64] =
{
	RO, KN, BI, KI, QU, BI, KN, RO,
	PA, PA, PA, PA, PA, PA, PA, PA,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
};

static uint32 player2_piece_mask[64] =
{
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	__, __, __, __, __, __, __, __,
	PA, PA, PA, PA, PA, PA, PA, PA,
	RO, KN, BI, QU, KI, BI, KN, RO,
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
					ntile->setColour(WHITE);
				else
					ntile->setColour(BLACK);
			}
			else
			{
				if (x % 2 == 0)
					ntile->setColour(BLACK);
				else
					ntile->setColour(WHITE);
			}

			tiles.push_back(ntile);

			// Place player1 pieces
			if (player1_piece_mask[x + (width * y)] == PA)
				pawns.push_back(new Pawn(ntile, PA));
			if (player1_piece_mask[x + (width * y)] == RO)
				rooks.push_back(new Rook(ntile, RO));
			if (player1_piece_mask[x + (width * y)] == KN)
				knights.push_back(new Knight(ntile, KN));
			if (player1_piece_mask[x + (width * y)] == BI)
				bishops.push_back(new Bishop(ntile, BI));
			if (player1_piece_mask[x + (width * y)] == QU)
				queens.push_back(new Queen(ntile, QU));
			if (player1_piece_mask[x + (width * y)] == KI)
				kings.push_back(new King(ntile, KI));
			// Place player2 pieces
			if (player2_piece_mask[x + (width * y)] == PA)
				pawns.push_back(new Pawn(ntile, PA));
			if (player2_piece_mask[x + (width * y)] == RO)
				rooks.push_back(new Rook(ntile, RO));
			if (player2_piece_mask[x + (width * y)] == KN)
				knights.push_back(new Knight(ntile, KN));
			if (player2_piece_mask[x + (width * y)] == BI)
				bishops.push_back(new Bishop(ntile, BI));
			if (player2_piece_mask[x + (width * y)] == QU)
				queens.push_back(new Queen(ntile, QU));
			if (player2_piece_mask[x + (width * y)] == KI)
				kings.push_back(new King(ntile, KI));
		}
	}

	//// Create white Pawns
	//for (int32 x = 0; x < width; x++)
	//{
	//	pawns[x + (width * y_white)] = new Pawn(getTile(x + (width * y_white)), white);
	//	pawns[x + (width * y_black)] = new Pawn(getTile(x + (width * y_black)), white);
	//}
}

Board::~Board()
{
	tiles.clear();
	pawns.clear();
}

void Board::drawTiles()
{
	for (std::vector<Tile>::size_type i = 0; i != tiles.size(); i++)
	{
		tiles[i]->draw(width, height);
		tiles[i]->drawOutline(width, height);
	}
}

void Board::drawPieces()
{
	for (std::vector<Pawn>::size_type i = 0; i != pawns.size(); i++)
	{
		pawns[i]->draw(width, height);
	}
	
	for (std::vector<Rook>::size_type i = 0; i != rooks.size(); i++)
	{
		rooks[i]->draw(width, height);
	}
	
	for (std::vector<Knight>::size_type i = 0; i != knights.size(); i++)
	{
		knights[i]->draw(width, height);
	}
	
	for (std::vector<Bishop>::size_type i = 0; i != bishops.size(); i++)
	{
		bishops[i]->draw(width, height);
	}
	
	for (std::vector<Queen>::size_type i = 0; i != queens.size(); i++)
	{
		queens[i]->draw(width, height);
	}
	
	for (std::vector<King>::size_type i = 0; i != kings.size(); i++)
	{
		kings[i]->draw(width, height);
	}
}