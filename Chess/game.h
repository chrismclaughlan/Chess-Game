#pragma once
#include "board.h"

const int32 MAX_ROUNDS = 10;

class Game
{
private:  // Business logic
	Board* boards[MAX_ROUNDS];

public:
	Game();
	~Game();

	Board* getBoardState(int32);

	void setBoardState(Board*, int32);

	int32 simulate(Input*, float);
};