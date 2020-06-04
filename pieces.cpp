#include <vector>
#include "pieces.h"
#include "render.h"
#include "board.h"

#define moveUp() if (r) idx -= width; else idx += width;
#define moveDown() if (r) idx += width; else idx -= width;
#define moveLeft() if (r) idx += 1; else idx -= 1;
#define moveRight() if (r) idx -= 1; else idx += 1;
#define moveDiagonalUpLeft() if (r) idx -= width - 1; else idx += width - 1;
#define moveDiagonalUpRight() if (r) idx -= width + 1; else idx += width + 1;
#define moveDiagonalDownLeft() if (r) idx -= -width - 1; else idx += -width - 1;
#define moveDiagonalDownRight() if (r) idx -= -width + 1; else idx += -width + 1;
#define POSSIBLE 0
#define POSSIBLE_WITH_PIECE 1
#define NOT_POSSIBLE 2

extern RenderState rs;

int32 Piece::checkPossible(std::vector<Tile*> tiles, int32 idx)
{
	//if (0 < idx < (width * height))
	if (idx > -1)
	{
		if (idx < width * height)
		{
			if (tiles[idx]->hasPiece())
			{
				Piece* piece = tiles[idx]->getPiece();
				if (piece->getColour() != colour)
				{
					// opponent's piece
					tiles[idx]->setPossibleMove(true);
					return POSSIBLE_WITH_PIECE;
				}
			}
			else
			{
				tiles[idx]->setPossibleMove(true);
				return POSSIBLE;
			}
		}
	}
	return NOT_POSSIBLE;
}

Pawn::Pawn(Tile* npos)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = 0x00FF00;
	has_moved = false;
};

Pawn::Pawn(Tile* npos, uint32 ncolour)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = ncolour;
	has_moved = false;
};

void Pawn::draw(int32 w, int32 h)
{
	float window_x_limit = (rs.width / (rs.height * render_scale));
	float window_y_limit = (rs.height / (rs.height * render_scale));
	float tile_x_size = window_x_limit / (w * 2);
	float tile_y_size = window_y_limit / (h * 2);
	float pawn_x_size = window_x_limit / (w * 4);
	float pawn_y_size = window_y_limit / (h * 4);
	float x = ((window_x_limit * position->getX()) / w) + tile_x_size;
	float y = ((window_y_limit * position->getY()) / h) + tile_y_size;
	
	Render::DrawRect(x, y, pawn_x_size, pawn_y_size, colour);
}

void Pawn::fillPossibleMoves(std::vector<Tile*> tiles, int32 current_idx, Player* this_player)
{
#define checkTile() if (checkPossible(tiles, idx) > POSSIBLE) return;

	int32 idx = current_idx;
	bool r = this_player->isReversed();

	moveUp();
	checkTile();

	if (!has_moved)
	{
		moveUp();
		checkTile();
	}
}

Rook::Rook(Tile* npos)
{
	position = npos;
	colour = 0x008000;
};

Rook::Rook(Tile* npos, uint32 ncolour)
{
	position = npos;
	colour = ncolour;
};

void Rook::draw(int32 w, int32 h)
{
	float window_x_limit = (rs.width / (rs.height * render_scale));
	float window_y_limit = (rs.height / (rs.height * render_scale));
	float tile_x_size = window_x_limit / (w * 2);
	float tile_y_size = window_y_limit / (h * 2);
	float pawn_x_size = window_x_limit / (w * 4);
	float pawn_y_size = window_y_limit / (h * 4);
	float x = ((window_x_limit * position->getX()) / w) + tile_x_size;
	float y = ((window_y_limit * position->getY()) / h) + tile_y_size;
	Render::DrawRect(x, y, pawn_x_size, pawn_y_size, colour);

	//if (selected)
	//	position->drawOutline(w, h, selection_colour, 1);
}

void Rook::fillPossibleMoves(std::vector<Tile*> tiles, int32 current_idx, Player* this_player)
{
#define checkTile()				if (checkPossible(tiles, idx) > POSSIBLE) break;
#define checkLeftBoundary()		if (r) { if ((idx + 1) % width == 0) break; } else { if (idx % width == 0) break; }
#define checkRightBoundary()	if (r) { if (idx % width == 0) break; } else { if ((idx + 1) % width == 0) break; }	

	int32 idx;
	bool r = this_player->isReversed();

	// up
	idx = current_idx;
	while (true)
	{
		moveUp();
		checkTile();
	}

	// down
	idx = current_idx;
	while (true)
	{
		moveDown();
		checkTile();
	}

	// left
	idx = current_idx;
	while (true)
	{
		checkLeftBoundary();
		moveLeft();
		checkTile();
	}

	// right
	idx = current_idx;
	while (true)
	{
		checkRightBoundary();
		moveRight();
		checkTile();
	}
}

Knight::Knight(Tile* npos)
{
	position = npos;
	colour = 0x00FFFF;
};

Knight::Knight(Tile* npos, uint32 ncolour)
{
	position = npos;
	colour = ncolour;
};

void Knight::draw(int32 w, int32 h)
{
	float window_x_limit = (rs.width / (rs.height * render_scale));
	float window_y_limit = (rs.height / (rs.height * render_scale));
	float tile_x_size = window_x_limit / (w * 2);
	float tile_y_size = window_y_limit / (h * 2);
	float pawn_x_size = window_x_limit / (w * 4);
	float pawn_y_size = window_y_limit / (h * 4);
	float x = ((window_x_limit * position->getX()) / w) + tile_x_size;
	float y = ((window_y_limit * position->getY()) / h) + tile_y_size;
	Render::DrawRect(x, y, pawn_x_size, pawn_y_size, colour);

	//if (selected)
	//	position->drawOutline(w, h, selection_colour, 1);
}

void Knight::fillPossibleMoves(std::vector<Tile*> tiles, int32 current_idx, Player* this_player)
{
#define checkTile()				checkPossible(tiles, idx);
#define checkLeftBoundary()		(idx + r % width == 0)  // r = 1 if reverse; 0 if not
#define checkRightBoundary()	((idx + 1 - r) % width == 0)  // r = 1 if reverse; 0 if not

	int32 idx;
	int32 r = this_player->isReversed();

	// up up left
	idx = current_idx;
	if (!checkLeftBoundary())
	{
		moveUp();
		moveDiagonalUpLeft();
		checkTile();
	}

	// up up right
	idx = current_idx;
	if (!checkRightBoundary())
	{
		moveUp();
		moveDiagonalUpRight();
		checkTile();
	}

	// down down left
	idx = current_idx;
	if (!checkLeftBoundary())
	{
		moveDown();
		moveDiagonalDownLeft();
		checkTile();
	}

	// down down right
	idx = current_idx;
	if (!checkRightBoundary())
	{
		moveDown();
		moveDiagonalDownRight();
		checkTile();
	}

	// left left up
	idx = current_idx;
	if (!checkLeftBoundary())
	{
		moveLeft();
		if (!checkLeftBoundary())
		{
			moveDiagonalUpLeft();
			checkTile();
		}
	}

	// right right up
	idx = current_idx;
	if (!checkRightBoundary())
	{
		moveRight();
		if (!checkRightBoundary())
		{
			moveDiagonalUpRight();
			checkTile();
		}
	}

	// left left down
	idx = current_idx;
	if (!checkLeftBoundary())
	{
		moveLeft();
		if (!checkLeftBoundary())
		{
			moveDiagonalDownLeft();
			checkTile();
		}
	}

	// right right down
	idx = current_idx;
	if (!checkRightBoundary())
	{
		moveRight();
		if (!checkRightBoundary())
		{
			moveDiagonalDownRight();
			checkTile();
		}
	}
}

Bishop::Bishop(Tile* npos)
{
	position = npos;
	colour = 0x008080;
};

Bishop::Bishop(Tile* npos, uint32 ncolour)
{
	position = npos;
	colour = ncolour;
};

void Bishop::draw(int32 w, int32 h)
{
	float window_x_limit = (rs.width / (rs.height * render_scale));
	float window_y_limit = (rs.height / (rs.height * render_scale));
	float tile_x_size = window_x_limit / (w * 2);
	float tile_y_size = window_y_limit / (h * 2);
	float pawn_x_size = window_x_limit / (w * 4);
	float pawn_y_size = window_y_limit / (h * 4);
	float x = ((window_x_limit * position->getX()) / w) + tile_x_size;
	float y = ((window_y_limit * position->getY()) / h) + tile_y_size;
	Render::DrawRect(x, y, pawn_x_size, pawn_y_size, colour);

	//if (selected)
	//	position->drawOutline(w, h, selection_colour, 1);
}

void Bishop::fillPossibleMoves(std::vector<Tile*> tiles, int32 current_idx, Player* this_player)
{
#define checkTile()				if (checkPossible(tiles, idx) > POSSIBLE) break;
#define checkLeftBoundary()		if (r) { if ((idx + 1) % width == 0) break; } else { if (idx % width == 0) break; }
#define checkRightBoundary()	if (r) { if (idx % width == 0) break; } else { if ((idx + 1) % width == 0) break; }	

	int32 idx;
	bool r = this_player->isReversed();

	// up left
	idx = current_idx;
	while (true)
	{
		checkLeftBoundary();
		moveDiagonalUpLeft();
		checkTile();
	}

	// up right
	idx = current_idx;
	while (true)
	{
		checkRightBoundary();
		moveDiagonalUpRight();
		checkTile();
	}

	// down left
	idx = current_idx;
	while (true)
	{
		checkLeftBoundary();
		moveDiagonalDownLeft();
		checkTile();
	}

	// down right
	idx = current_idx;
	while (true)
	{
		checkRightBoundary();
		moveDiagonalDownRight();
		checkTile();
	}
}

Queen::Queen(Tile* npos)
{
	position = npos;
	colour = 0x0000FF;
};

Queen::Queen(Tile* npos, uint32 ncolour)
{
	position = npos;
	colour = ncolour;
};

void Queen::draw(int32 w, int32 h)
{
	float window_x_limit = (rs.width / (rs.height * render_scale));
	float window_y_limit = (rs.height / (rs.height * render_scale));
	float tile_x_size = window_x_limit / (w * 2);
	float tile_y_size = window_y_limit / (h * 2);
	float pawn_x_size = window_x_limit / (w * 4);
	float pawn_y_size = window_y_limit / (h * 4);
	float x = ((window_x_limit * position->getX()) / w) + tile_x_size;
	float y = ((window_y_limit * position->getY()) / h) + tile_y_size;
	Render::DrawRect(x, y, pawn_x_size, pawn_y_size, colour);

	//if (selected)
	//	position->drawOutline(w, h, selection_colour, 1);
}

void Queen::fillPossibleMoves(std::vector<Tile*> tiles, int32 current_idx, Player* this_player)
{
#define checkTile()				if (checkPossible(tiles, idx) > POSSIBLE) break;
#define checkLeftBoundary()		if (r) { if ((idx + 1) % width == 0) break; } else { if (idx % width == 0) break; }
#define checkRightBoundary()	if (r) { if (idx % width == 0) break; } else { if ((idx + 1) % width == 0) break; }

	int32 idx;
	bool r = this_player->isReversed();

	// up
	idx = current_idx;
	while (true)
	{
		moveUp();
		checkTile();
	}

	// down
	idx = current_idx;
	while (true)
	{
		moveDown();
		checkTile();
	}

	// left
	idx = current_idx;
	while (true)
	{
		checkLeftBoundary();
		moveLeft();
		checkTile();
	}

	// right
	idx = current_idx;
	while (true)
	{
		checkRightBoundary();
		moveRight();
		checkTile();
	}

	// up left
	idx = current_idx;
	while (true)
	{
		checkLeftBoundary();
		moveDiagonalUpLeft();
		checkTile();
	}

	// up right
	idx = current_idx;
	while (true)
	{
		checkRightBoundary();
		moveDiagonalUpRight();
		checkTile();
	}

	// down left
	idx = current_idx;
	while (true)
	{
		checkLeftBoundary();
		moveDiagonalDownLeft();
		checkTile();
	}

	// down right
	idx = current_idx;
	while (true)
	{
		checkRightBoundary();
		moveDiagonalDownRight();
		checkTile();
	}
}

King::King(Tile* npos)
{
	position = npos;
	colour = 0x0000FF;
};

King::King(Tile* npos, uint32 ncolour)
{
	position = npos;
	colour = ncolour;
};

void King::draw(int32 w, int32 h)
{
	float window_x_limit = (rs.width / (rs.height * render_scale));
	float window_y_limit = (rs.height / (rs.height * render_scale));
	float tile_x_size = window_x_limit / (w * 2);
	float tile_y_size = window_y_limit / (h * 2);
	float pawn_x_size = window_x_limit / (w * 4);
	float pawn_y_size = window_y_limit / (h * 4);
	float x = ((window_x_limit * position->getX()) / w) + tile_x_size;
	float y = ((window_y_limit * position->getY()) / h) + tile_y_size;
	Render::DrawRect(x, y, pawn_x_size, pawn_y_size, colour);

	//if (selected)
	//	position->drawOutline(w, h, selection_colour, 1);
}

void King::fillPossibleMoves(std::vector<Tile*> tiles, int32 current_idx, Player* this_player)
{
#define checkTile()				checkPossible(tiles, idx);
#define checkLeftBoundary()		(idx + r % width == 0)  // r = 1 if reverse; 0 if not
#define checkRightBoundary()	((idx + 1 - r) % width == 0)  // r = 1 if reverse; 0 if not

	int32 idx;
	int32 r = this_player->isReversed();

	// up left
	idx = current_idx;
	if (!checkLeftBoundary())
	{
		moveDiagonalUpLeft();
		checkTile();
	}

	// up
	idx = current_idx;
	moveUp();
	checkTile();

	// up right
	idx = current_idx;
	if (!checkRightBoundary())
	{
		moveDiagonalUpRight();
		checkTile();
	}

	// left
	idx = current_idx;
	if (!checkLeftBoundary())
	{
		moveLeft();
		checkTile();
	}

	// right
	idx = current_idx;
	if (!checkRightBoundary())
	{
		moveRight();
		checkTile();
	}

	// down left
	idx = current_idx;
	if (!checkLeftBoundary())
	{
		moveDiagonalDownLeft();
		checkTile();
	}

	// down
	idx = current_idx;
	moveDown();
	checkTile();

	// down right
	idx = current_idx;
	if (!checkRightBoundary())
	{
		moveDiagonalDownRight();
		checkTile();
	}
}
