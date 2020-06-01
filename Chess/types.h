#pragma once

// Handle input
#define is_down(b) (input->buttons[b].is_down)
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

// Handle return codes
#define CONTINUE_GAME 0
#define GAME_END 1

typedef char			int8;
typedef unsigned char	uint8;
typedef short			int16;
typedef unsigned short	uint16;
typedef int				int32;
typedef unsigned int	uint32;
typedef long			int64;
typedef unsigned long	uint64;

struct ButtonState
{
	bool is_down;
	bool has_changed;
};

enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT,  // always last
};

struct Input
{
	ButtonState buttons[BUTTON_COUNT];
};