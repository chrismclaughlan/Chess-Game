#pragma once
typedef char			int8;
typedef unsigned char	uint8;
typedef short			int16;
typedef unsigned short	uint16;
typedef int				int32;
typedef unsigned int	uint32;
typedef long			int64;
typedef unsigned long	uint64;

// Handle input
#define is_down(b) (input->buttons[b].is_down)
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].has_changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].has_changed)

// Handle return codes
#define GAME_END -1
#define CONTINUE_GAME 0
#define SELECT_ENTER 1

static const uint32 RED = 0xff0000;
static const uint32 BLUE = 0x0000ff;
static const uint32 WHITE = 0xffffff;
static const uint32 BLACK = 0x000000;
static const uint32 BROWN = 0x581845;
static const uint32 BEIGE = 0xF5F5DC;