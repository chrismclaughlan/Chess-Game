#pragma once

class Piece
{
private:
	char* name;

public:
	Piece();
	~Piece();

	char* getName() { return this->name; };

	void setName(char* nname) { this->name = nname; };
};