#include "render.h"

RenderState rs;

namespace Render
{
	static void
	ClearScreen(uint32 colour)
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
}