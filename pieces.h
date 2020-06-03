#pragma once
#include "tile.h"
#include "types.h"

class Tile;

class Piece
{
protected:
	Tile* position;
	uint32 colour;
	//bool selected;

public:
	Piece() { position = nullptr; colour = 0x000000; };
	~Piece() {};

	//char* getName() { return this->name; };
	Tile* getPosition() { return position; };
	uint32 getColour() { return colour; };
	//bool isSelected() { return selected; };

	//void setName(char* nname) { this->name = nname; };
	void setPosition(Tile* npos) { position = npos; };
	void setColour(uint32 ncolour) { colour = ncolour; };

	//void select();
	//void deSelect();

	virtual void draw(int32, int32) {};
};


class Pawn : public Piece
{
private:
	bool has_moved = false;

public:
	Pawn(Tile*);
	Pawn(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class Rook : public Piece
{
private:

public:
	Rook(Tile*);
	Rook(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class Knight : public Piece
{
private:

public:
	Knight(Tile*);
	Knight(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class Bishop : public Piece
{
private:

public:
	Bishop(Tile*);
	Bishop(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class Queen : public Piece
{
private:

public:
	Queen(Tile*);
	Queen(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};

class King : public Piece
{
private:

public:
	King(Tile*);
	King(Tile*, uint32);

	//Tile** possibleMoves();
	void draw(int32, int32);
};