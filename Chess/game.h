#pragma once
#include "board.h"

const int32 MAX_ROUNDS = 1000;

class Game
{
public:  // Singleton logic
	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}
private:
	Game() {}
	Game(Game const&);
	void operator=(Game const&);
public:
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

private:  // Business logic
	Board boards[MAX_ROUNDS];

public:
	Board* getBoardState(int32 round) { return &boards[round]; };

	int32 simulate(Input* input, float dt);
};