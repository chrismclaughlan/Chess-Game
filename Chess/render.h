#pragma once
#include <windows.h>
#include "types.h"

struct RenderState
{
	int32 width;
	int32 height;
	void* memory;
	BITMAPINFO bitmapinfo;
};

extern RenderState rs;
namespace Render
{
	void ClearScreen(uint32 colour);
}