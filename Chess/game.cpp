#include "types.h"
#include "render.cpp"
#include "game.h"

Game::Game()
{

}

Game::~Game()
{
	delete[] boards;
}

Board* Game::getBoardState(int32 round)
{
	return boards[round];
}

void Game::setBoardState(Board* nboard, int32 round)
{
	boards[round] = nboard;
}

int32 Game::simulate(Input* input, float dt)
{
	// Handle input
	//if (is_down(BUTTON_LUP));
	//if (is_down(BUTTON_DOWN));
	//if (is_down(BUTTON_LEFT));
	//if (is_down(BUTTON_RIGHT));

	// Handle actions

	// Handle rendering
	Render::ClearScreen(0xffffff);
	
	return CONTINUE_GAME;
}