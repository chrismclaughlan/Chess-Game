#pragma once
#include <vector>
#include "board.h"
#include "render.h"
#include "input.h"

const int32 MAX_ROUNDS = 100;

class Game
{
private:  // Business logic
	std::vector<Board*> boards;
	std::vector<Board*>::iterator current_board;
	//std::vector<Board*>::iterator	round;

public:
	Game();
	~Game();

	void setBoardState(Board*, int32);
	//void setRound(int32);

	Board* getBoardState(int32);
	//int32 getRound();

	int32 simulate(Input*, float);

	void progress();
};