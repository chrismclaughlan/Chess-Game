#include "board.h"

Tile::Tile(int32 nx, int32 ny)
{
	x = nx;
	y = ny;
}

Tile::~Tile()
{

}

Board::Board()
{
	int i = 0;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			tiles[i++] = new Tile(x, y);
		}
	}
}

Board::~Board()
{
	delete[] tiles;
}