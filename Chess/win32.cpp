#include <windows.h>

#include "types.h"
#include "game.h"
#include "render.h"

const char* GAME_NAME = "Chess";
static bool is_running = true;
const int32 WINDOW_WIDTH = 800;
const int32 WINDOW_HEIGHT = 600;

static RenderState rs;

LRESULT CALLBACK
window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
		is_running = false;
	} break;
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		rs.width = rect.right - rect.left;
		rs.height = rect.bottom - rect.top;

		int32 buff_size = rs.width * rs.height * sizeof(unsigned int);
		if (rs.memory)
		{
			VirtualFree(rs.memory, 0, MEM_RELEASE);
		}
		rs.memory = VirtualAlloc(0, buff_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		rs.bitmapinfo.bmiHeader.biSize = sizeof(rs.bitmapinfo);
		rs.bitmapinfo.bmiHeader.biWidth = rs.width;
		rs.bitmapinfo.bmiHeader.biHeight = rs.height;
		rs.bitmapinfo.bmiHeader.biPlanes = 1;
		rs.bitmapinfo.bmiHeader.biBitCount = 32;
		rs.bitmapinfo.bmiHeader.biCompression = BI_RGB;
	} break;

	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

int WinMain
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = window_callback;

	RegisterClass(&window_class);

	HWND window = CreateWindow(window_class.lpszClassName, GAME_NAME,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	float delta_time = 0.016666f;  // TODO
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}

	while (is_running)
	{
		MSG message;
		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			input.buttons[i].has_changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			switch (message.message)
			{
			case WM_KEYUP:
			case WM_KEYDOWN:
			{
				uint32 vk_code = (uint32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk:\
{\
input.buttons[b].has_changed = is_down != input.buttons[b].is_down;\
input.buttons[b].is_down = is_down;\
} break;\

				switch (vk_code)
				{
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
				}
			} break;

			default:
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}  // PeekMessage ...

		// Simulate
		Game::getInstance().simulate(&input, delta_time);

		// Render
		StretchDIBits(hdc, 0, 0, rs.width, rs.height, 0, 0,
			rs.width, rs.height, rs.memory,
			&rs.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);


		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}
}