#include <vector>
#include "types.h"
#include "game.h"
#include "render.h"

Game::Game()
{
	boards.push_back(new Board());
	current_board = boards.begin();
}

Game::~Game()
{
	boards.clear();
}

void Game::setBoardState(Board* nboard, int32 round)
{
	boards[round] = nboard;
}

Board* Game::getBoardState(int32 round)
{
	return boards[round];
}

int32 Game::simulate(Input* input, float dt)
{
	Board* board = *current_board;
	Player* player = board->getCurrentPlayer();

	// Handle input
	if (pressed(BUTTON_UP))
		player->selectUp();
	if (pressed(BUTTON_DOWN))
		player->selectDown();
	if (pressed(BUTTON_LEFT))
		player->selectLeft();
	if (pressed(BUTTON_RIGHT))
		player->selectRight();
	if (pressed(BUTTON_SPACE))
		player->select();
	if (pressed(BUTTON_RETURN))
	{
		// TODO check valid turn
		player->selectClear();
		board->nextPlayer();
	}
	if (pressed(BUTTON_ESCAPE))
	{
		player->selectCancel();
	}

	// Handle actions

	// Handle rendering
	board->drawTiles();
	board->drawPlayers();
	board->drawPlayerSelection();
	board->drawPlayerCursor();  // After selection

	return CONTINUE_GAME;
}

void Game::progress()
{
	//Board* b;
	//b = *current_board;
	//std::advance(current_board, 1);
}