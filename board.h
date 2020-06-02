#pragma once
#include <vector>
#include "types.h"
#include "pieces.h"
#include "tile.h"

static const uint32 __ = 0xaaaaaa;  // empty space
static const uint32 PA = 0x00FF00;  // pawn
static const uint32 RO = 0x008000;  // rook
static const uint32 KN = 0x00FFFF;  // knight
static const uint32 BI = 0x008080;  // bishop
static const uint32 QU = 0x0000FF;  // queen
static const uint32 KI = 0x0000FF;  // king

class Board
{
private:
	int32 width = 8;
	int32 height = 8;
	uint32 player1 = 0x00ffff;
	uint32 player2 = 0x00ff00;

	int32 num_pawns = 8;  // per player

	std::vector<Tile*>		tiles;
	std::vector<Pawn*>		pawns;
	std::vector<Rook*>		rooks;
	std::vector<Knight*>	knights;
	std::vector<Bishop*>	bishops;
	std::vector<Queen*>		queens;
	std::vector<King*>		kings;

public:
	Board();
	~Board();

	void setTile(Tile* ntile, int32 pos) { this->tiles[pos] = ntile; };
	void setPawn(Pawn* npawn, int32 pos) { this->pawns[pos] = npawn; };
	void setPawn(Rook* nrook, int32 pos) { this->rooks[pos] = nrook; };
	void setPawn(Knight* nknight, int32 pos) { this->knights[pos] = nknight; };
	void setPawn(Bishop* nbishop, int32 pos) { this->bishops[pos] = nbishop; };
	void setPawn(Queen* nqueen, int32 pos) { this->queens[pos] = nqueen; };
	void setPawn(King* nking, int32 pos) { this->kings[pos] = nking; };

	Tile* getTile(int32 pos) { return tiles[pos]; };
	Pawn* getPawn(int32 pos) { return pawns[pos]; };
	Rook* getRook(int32 pos) { return rooks[pos]; };
	Knight* getKnight(int32 pos) { return knights[pos]; };
	Bishop* getBishop(int32 pos) { return bishops[pos]; };
	Queen* getQueen(int32 pos) { return queens[pos]; };
	King* getKing(int32 pos) { return kings[pos]; };

	void drawTiles();
	void drawPieces();
};