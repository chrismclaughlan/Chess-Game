#pragma once

#include "tile.h"

class Piece
{
protected:
	char* name;
	Tile position;

public:
	Piece() {};
	~Piece() {};

	char* getName() { return this->name; };
	Tile getPosition() { return this->position; };

	void setName(char* nname) { this->name = nname; };
	void setPosition(Tile npos) { this->position = npos; };
};


class Pawn : public Piece
{
private:
	bool has_moved = false;

public:
	Pawn();
	~Pawn();

	//Tile** possibleMoves();
};