#pragma once
#include "types.h"

static const float outline_tickness = 0.5;

class Tile
{
private:
	int32 x;
	int32 y;
	uint32 colour;

public:
	Tile(int32, int32);
	Tile(int32, int32, uint32);
	~Tile();

	int32 getX() { return x; };
	int32 getY() { return y; };
	uint32 getColour() { return colour; };

	void setX(int32 nx) { x = nx; };
	void setY(int32 ny) { y = ny; };
	void setColour(uint32 ncolour) { colour = ncolour; };

	void draw(int32, int32);
	void drawOutline(int32, int32);
};