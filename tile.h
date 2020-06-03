#pragma once
#include "pieces.h"
#include "types.h"

//static const float outline_tickness = 0.5;

static const uint32 selection_colour = GREEN;

class Piece;

class Tile
{
private:
	int32 x;
	int32 y;
	uint32 colour;

	Piece* piece;
	bool selected;

public:
	Tile(int32, int32);
	Tile(int32, int32, Piece*);
	Tile(int32, int32, uint32);
	~Tile();

	void setX(int32 nx) { x = nx; };
	void setY(int32 ny) { y = ny; };
	void setColour(uint32 ncolour) { colour = ncolour; };
	void setPiece(Piece* npiece) { piece = npiece; };
	//void removePiece() { piece = nullptr; };

	int32 getX() { return x; };
	int32 getY() { return y; };
	uint32 getColour() { return colour; };
	Piece* getPiece() { return piece; };

	void draw(int32, int32);
	void drawOutline(int32, int32, uint32, float);
	void drawPiece(int32, int32);

	void select();
	void deSelect();
	bool isSelected() { return selected; };
};