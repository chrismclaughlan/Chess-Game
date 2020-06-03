#pragma once
// NEW
#include <windows.h>
#include "types.h"

struct RenderState
{
	int32 width;
	int32 height;
	void* memory;
	BITMAPINFO bitmapinfo;
};

const float render_scale = 0.01f;

class Render
{
public:
	static inline void clamp(int32, int32*, int32);
	static void ClearScreen(uint32);
	static void DrawRectP(int32, int32, int32, int32, uint32);
	static void DrawRect(float, float, float, float, uint32);
	static inline void DrawPoint(int32, int32, uint32);
	static void DrawLineP(int32, int32, int32, int32, uint32);
	static void DrawLine(float, float, float, float, uint32);
	static void DrawRectO(float, float, float, float, uint32, float);
	static void DrawOutline(float, float, int32, int32, uint32, float);
};