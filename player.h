#pragma once
#include <vector>
#include "board.h"
#include "pieces.h"

//static uint32 player1_piece_mask[64] =
//{
//	RO, KN, BI, KI, QU, BI, KN, RO,
//	PA, PA, PA, PA, PA, PA, PA, PA,
//	__, __, __, __, __, __, __, __,
//	__, __, __, __, __, __, __, __,
//	__, __, __, __, __, __, __, __,
//	__, __, __, __, __, __, __, __,
//	__, __, __, __, __, __, __, __,
//	__, __, __, __, __, __, __, __,
//};

enum
{
	EMPT,
	PAWN,
	ROOK,
	KNIG,
	BISH,
	QUEE,
	KING,

	PIECE_AMOUNT,
};

class Board;

class Player
{
private:
	std::vector<Pawn*>		pawns;
	std::vector<Rook*>		rooks;
	std::vector<Knight*>	knights;
	std::vector<Bishop*>	bishops;
	std::vector<Queen*>		queens;
	std::vector<King*>		kings;

	Board* parent;
	std::vector<Tile*>::iterator current_tile;
	int32 selection_colour;

public:
	//Player();
	Player(Board*, int32[], int32, int32, const uint32, const uint32);
	~Player();

	void setPawn(Pawn* npawn, int32 pos) { this->pawns[pos] = npawn; };
	void setPawn(Rook* nrook, int32 pos) { this->rooks[pos] = nrook; };
	void setPawn(Knight* nknight, int32 pos) { this->knights[pos] = nknight; };
	void setPawn(Bishop* nbishop, int32 pos) { this->bishops[pos] = nbishop; };
	void setPawn(Queen* nqueen, int32 pos) { this->queens[pos] = nqueen; };
	void setPawn(King* nking, int32 pos) { this->kings[pos] = nking; };

	Pawn* getPawn(int32 pos) { return pawns[pos]; };
	Rook* getRook(int32 pos) { return rooks[pos]; };
	Knight* getKnight(int32 pos) { return knights[pos]; };
	Bishop* getBishop(int32 pos) { return bishops[pos]; };
	Queen* getQueen(int32 pos) { return queens[pos]; };
	King* getKing(int32 pos) { return kings[pos]; };

	void draw(int32, int32);
	void drawSelection(int32, int32);

	void selectUp();
	void selectDown();
	void selectLeft();
	void selectRight();
	void selectEnter();
	void selectCancel();

	void checkTile(Tile*);
};