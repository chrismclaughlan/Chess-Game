#include <vector>
#include "types.h"
#include "game.h"
#include "render.h"

Game::Game()
{
	//boards = (Board**)malloc(MAX_ROUNDS * sizeof(Board));
	boards.push_back(new Board());
	round = 0;
}

Game::~Game()
{
	boards.clear();
}

void Game::setBoardState(Board* nboard, int32 round)
{
	boards[round] = nboard;
}

void Game::setRound(int32 nround)
{
	round = nround;
}

Board* Game::getBoardState(int32 round)
{
	return boards[round];
}

int32 Game::getRound()
{
	return round;
}

int32 Game::simulate(Input* input, float dt)
{
	Board* board = boards[round];

	// Handle input
	if (is_down(BUTTON_UP))		;
	if (is_down(BUTTON_DOWN))	;
	if (is_down(BUTTON_LEFT))	;
	if (is_down(BUTTON_RIGHT))	;

	// Handle actions

	// Handle rendering
	board->drawTiles();
	//board->drawPieces();

	return CONTINUE_GAME;
}