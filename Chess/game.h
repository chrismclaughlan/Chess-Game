#pragma once
#include "board.h"

const int32 MAX_ROUNDS = 1000;

class Game
{
private:  // Business logic
	Board boards[MAX_ROUNDS];

public:
	Board* getBoardState(int32 round) { return &boards[round]; };

	int32 simulate(Input* input, float dt);
};