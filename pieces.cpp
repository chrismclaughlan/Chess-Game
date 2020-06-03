#include "pieces.h"
#include "render.h"

extern RenderState rs;

//void Piece::select()
//{
//	selected = true;
//}
//
//void Piece::deSelect()
//{
//	selected = false;
//}

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

//Tile** Pawn::possibleMoves()
//{
//	if (!this->has_moved)
//	{
//		// Can move 2x or 1x
//	}
//
//	return ;
//}

Rook::Rook(Tile* npos)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = 0x008000;
};

Rook::Rook(Tile* npos, uint32 ncolour)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = ncolour;
};

void Rook::draw(int32 w, int32 h)
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

Knight::Knight(Tile* npos)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = 0x00FFFF;
};

Knight::Knight(Tile* npos, uint32 ncolour)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = ncolour;
};

void Knight::draw(int32 w, int32 h)
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

Bishop::Bishop(Tile* npos)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = 0x008080;
};

Bishop::Bishop(Tile* npos, uint32 ncolour)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = ncolour;
};

void Bishop::draw(int32 w, int32 h)
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

Queen::Queen(Tile* npos)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = 0x0000FF;
};

Queen::Queen(Tile* npos, uint32 ncolour)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = ncolour;
};

void Queen::draw(int32 w, int32 h)
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

King::King(Tile* npos)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = 0x0000FF;
};

King::King(Tile* npos, uint32 ncolour)
{
	//this->name = (char*)"Pawn";
	position = npos;
	colour = ncolour;
};

void King::draw(int32 w, int32 h)
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
