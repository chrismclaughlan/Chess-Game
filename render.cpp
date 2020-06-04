#include "render.h"

extern RenderState rs;

inline void Render::clamp
(int32 min, int32* val, int32 max)
{
	if (*val < min) *val = min;
	else if (*val > max) *val = max;
}

void Render::ClearScreen
(uint32 colour)
{
	uint32* pixel = (uint32*)rs.memory;
	for (int32 y = 0; y < rs.height; y++)
	{
		for (int32 x = 0; x < rs.width; x++)
		{
			*pixel++ = colour;
		}
	}
}

void Render::DrawRectP
(int32 x1, int32 y1, int32 x2, int32 y2, uint32 colour)
{
	clamp(0, &x1, rs.width);
	clamp(0, &x2, rs.width);
	clamp(0, &y1, rs.height);
	clamp(0, &y2, rs.height);

	for (int32 y = y1; y < y2; y++)
	{
		uint32* pixel = (uint32*)rs.memory + x1
			+ (y * rs.width);
		for (int32 x = x1; x < x2; x++)
		{
			*pixel++ = colour;
		}
	}
}

void Render::DrawRect
(float x, float y, float w, float h, uint32 colour)
{
	x *= rs.height * render_scale;
	y *= rs.height * render_scale;
	w *= rs.height * render_scale;
	h *= rs.height * render_scale;

	// Convert to pixels
	int32 x1 = x - w;
	int32 x2 = x + w;
	int32 y1 = y - h;
	int32 y2 = y + h;
	DrawRectP(x1, y1, x2, y2, colour);
}

inline void
Render::DrawPoint(int32 x, int32 y, uint32 colour)
{
	clamp(0, &x, rs.width - 1);
	clamp(0, &y, rs.height - 1);

	uint32* pixel = (uint32*)rs.memory + x + (y * rs.width);
	*pixel = colour;
}

void Render::DrawLineP
(int32 x1, int32 y1, int32 x2, int32 y2, uint32 colour)
{
	int32 dx, sx, dy, sy, err, e2;
	dx = abs(x2 - x1);
	dy = -(abs(y2 - y1));
	if (x1 < x2)
		sx = 1;
	else
		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (true)
	{
		DrawPoint(x1, y1, colour);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void Render::DrawLine
(float x1, float y1, float x2, float y2, uint32 colour)
{
	x1 *= rs.height * render_scale;
	y1 *= rs.height * render_scale;
	x2 *= rs.height * render_scale;
	y2 *= rs.height * render_scale;

	DrawLineP(x1, y1, x2, y2, colour);
}

void Render::DrawRectO
(float x1, float y1, float x2, float y2, uint32 colour, float thickness)
{
	thickness *= rs.height * render_scale;
	x1 *= rs.height * render_scale;
	y1 *= rs.height * render_scale;
	x2 *= rs.height * render_scale;
	y2 *= rs.height * render_scale;

	// Convert to pixels
	int32 t = thickness;
	int32 x1_ = x1;
	int32 x2_ = x2;
	int32 y1_ = y1;
	int32 y2_ = y2;
	DrawRectP(x1_, y1_, x1_+t, y2_, colour);
	DrawRectP(x1_, y2_-t, x2_, y2_, colour);
	DrawRectP(x2_ - t, y1_, x2_, y2_, colour);
	DrawRectP(x1_, y1_, x2_, y1_+t, colour);
}

void Render::DrawOutline
(float x, float y, int32 w, int32 h, uint32 colour, float thickness)
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

void Render::DrawTriangleP
(int32 x1, int32 y1, int32 x2, int32 y2, uint32 colour)
{
	clamp(0, &x1, rs.width);
	clamp(0, &x2, rs.width);
	clamp(0, &y1, rs.height);
	clamp(0, &y2, rs.height);

	/*
			   x2, y2
			 /		|
		/			|
	x1,y1 ----------+
	

	*/

	float m;
	m = (y2 - y1) / (x2 - x1);

	/*
	y = mx
	*/

	for (int32 y = y1; y < y2; y++)
	{
		int32 new_x = (y + x1) / m;
		uint32* pixel = (uint32*)rs.memory + new_x + (y * rs.width);
		for (int32 x = new_x; x < x2; x++)
		{
			*pixel++ = colour;
		}
	}
}

void Render::DrawTriangle
(float x1, float y1, float x2, float y2, uint32 colour)
{
	x1 *= rs.height * render_scale;
	y1 *= rs.height * render_scale;
	x2 *= rs.height * render_scale;
	y2 *= rs.height * render_scale;

	DrawTriangleP((int32)x1, (int32)y1, (int32)x2, (int32)y2, colour);
}