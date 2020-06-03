#pragma once
#include <vector>
#include "board.h"
#include "pieces.h"

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
	std::vector<Piece*>		pieces;

	Board* parent;
	std::vector<Tile*>::iterator current_tile;
	std::vector<Tile*> selected_tiles;
	int32 cursor_colour;

public:
	//Player();
	Player(Board*, int32[], int32, int32, const uint32, const uint32);
	~Player();

	void draw(int32, int32);
	void drawCursor(int32, int32);
	void drawSelection(int32, int32);

	void selectUp();
	void selectDown();
	void selectLeft();
	void selectRight();
	void select();
	void selectCancel();
	void selectClear();

	void checkTile(Tile*);
};