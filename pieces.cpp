#include <vector>
#include "pieces.h"
#include "render.h"
#include "board.h"

#define moveUp(r) if (r) idx -= width; else idx += width;
#define moveDown(r) if (r) idx += width; else idx -= width;
#define moveLeft(r) if (r) idx += 1; else idx -= 1;
#define moveRight(r) if (r) idx -= 1; else idx += 1;
#define moveDiagonalUpLeft(r) if (r) idx -= width - 1; else idx += width - 1;
#define moveDiagonalUpRight(r) if (r) idx -= width + 1; else idx += width + 1;
#define moveDiagonalDownLeft(r) if (r) idx -= -width - 1; else idx += -width - 1;
#define moveDiagonalDownRight(r) if (r) idx -= -width + 1; else idx += -width + 1;
#define POSSIBLE 0
#define POSSIBLE_WITH_PIECE 1
#define NOT_POSSIBLE 2

extern RenderState rs;

int32 Piece::checkPossible(std::vector<Tile*> tiles, int32 idx)
{
	//if (0 < idx < (width * height))
	if (idx > 0)
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
	//Render::DrawRect(x + TILE_SIZE, y + TILE_SIZE, TILE_SIZE, TILE_SIZE, colour);
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

void Pawn::fillPossibleMoves(std::vector<Tile*> tiles, int32 current_idx, Player* this_player)
{
#define check() if (checkPossible(tiles, idx) && (POSSIBLE_WITH_PIECE | NOT_POSSIBLE)) return;

	int32 idx = current_idx;
	bool r = this_player->isReversed();

	moveUp(r);
	check();

	if (!has_moved)
	{
		moveUp(r);
		check();
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
#define check() if (checkPossible(tiles, idx) && (POSSIBLE_WITH_PIECE | NOT_POSSIBLE)) break;

	int32 idx;
	bool r = this_player->isReversed();

	idx = current_idx;
	while (true)
	{
		moveUp(r);
		check();
	}

	idx = current_idx;
	while (true)
	{
		moveDown(r);
		check();
	}

	//idx = current_idx;
	//while (true)
	//{
	//	moveLeft(r);
	//	check();
	//}

	//idx = current_idx;
	//while (true)
	//{
	//	moveRight(r);
	//	check();
	//}
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
	int32 idx = current_idx;
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
	int32 idx = current_idx;
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
	int32 idx = current_idx;
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
	int32 idx = current_idx;
}
