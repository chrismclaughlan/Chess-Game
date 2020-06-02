#pragma once
#include "types.h"

class Tile
{
private:
	int32 x;
	int32 y;

public:
	Tile();
	Tile(int32, int32);
	~Tile();

	int32 getX() { return this->x; };
	int32 getY() { return this->y; };

	void setX(int32 nx) { this->x = nx; };
	void setY(int32 ny) { this->y = ny; };
};

class Board
{
private:
	Tile* tiles[64];

public:
	Board();
	~Board();

	void setTile(Tile* ntile, int32 pos) { this->tiles[pos] = ntile; };

	Tile* getTile(int32 pos) { return tiles[pos]; };
};