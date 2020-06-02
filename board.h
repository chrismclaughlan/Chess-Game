#pragma once
#include <vector>
#include "types.h"
#include "pieces.h"
#include "tile.h"
#include "player.h"

class Player;

class Board
{
private:
	int32 width = 8;
	int32 height = 8;

	std::vector<Tile*>				tiles;
	std::vector<Player*>			players;
	std::vector<Player*>::iterator	current_player;

public:
	Board();
	Board(const Board& prev);
	~Board();

	void setTile(Tile* ntile, int32 pos) { this->tiles[pos] = ntile; };

	Tile* getTile(int32 pos) { return tiles[pos]; };

	void drawTiles();
	void drawOutlines();
	void drawPieces();
	void drawPlayers();
};