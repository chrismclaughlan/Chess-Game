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
class Piece;

class Player
{
private:
	std::vector<Piece*>		pieces;

	Board* parent;
	std::vector<Tile*>::iterator current_tile;
	std::vector<Tile*> selected_tiles;
	int32 cursor_colour;
	int32 colour;
	bool reverse;

public:
	//Player();
	Player(Board*, int32[], int32, int32, const uint32, const uint32, bool);
	~Player();

	uint32 getColour() { return colour; };
	bool isReversed() { return reverse; };

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

	void calculatePossibleMoves();
	void clearPossibleMoves();

	bool hasPiece(Piece*);
	bool validateTurn();
};