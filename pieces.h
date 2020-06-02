#pragma once
#include "tile.h"
#include "types.h"

class Piece
{
protected:
	Tile* position;
	uint32 colour;

public:
	Piece() { position = nullptr; colour = 0x000000; };
	~Piece() {};

	//char* getName() { return this->name; };
	//Tile* getPosition() { return position; };
	uint32 getColour() { return colour; };

	//void setName(char* nname) { this->name = nname; };
	void setPosition(Tile* npos) { position = npos; };
	void setColour(uint32 ncolour) { colour = ncolour; };
};


class Pawn : public Piece
{
private:
	bool has_moved = false;

public:
	Pawn(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class Rook : public Piece
{
private:

public:
	Rook(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class Knight : public Piece
{
private:

public:
	Knight(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class Bishop : public Piece
{
private:

public:
	Bishop(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class Queen : public Piece
{
private:

public:
	Queen(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class King : public Piece
{
private:

public:
	King(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};