#include "types.h"
#include "render.h"
#include "tile.h"

extern RenderState rs;

Tile::Tile(int32 nx, int32 ny)
{
	x = nx;
	y = ny;
	colour = 0;
}

Tile::Tile(int32 nx, int32 ny, uint32 ncolour)
{
	x = nx;
	y = ny;
	colour = ncolour;
}

Tile::~Tile()
{

}

void Tile::draw(int32 w, int32 h)
{
	float window_x_limit = (rs.width / (rs.height * render_scale));
	float window_y_limit = (rs.height / (rs.height * render_scale));
	float tile_x_size = window_x_limit / w;
	float tile_y_size = window_y_limit / h;
	Render::DrawRect((window_x_limit * x / w) + tile_x_size,
		(window_y_limit * y / h) + tile_y_size, tile_x_size, tile_y_size, colour);
}

void Tile::drawOutline(int32 w, int32 h, uint32 colour, float thickness)
{
	float window_x_limit = (rs.width / (rs.height * render_scale));
	float window_y_limit = (rs.height / (rs.height * render_scale));
	float tile_x_size = window_x_limit / w;
	float tile_y_size = window_y_limit / h;
	float x1 = (window_x_limit * x / h);
	float y1 = (window_y_limit * y / h);
	float x2 = (window_x_limit * x / h) + tile_x_size;
	float y2 = (window_y_limit * y / h) + tile_y_size;
	Render::DrawRectO(x1, y1, x2, y2, colour, thickness);
}