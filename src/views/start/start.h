#include <SDL.h>

#include "views/index.h"

#include "utils/sdl.h"
#include "input/input.h"
#include "charset/charset.h"


#ifndef START_H
#define START_H

struct StartLayout
{
	char* title;
	char* message;

	int blink_flag;
	int blink_frame_count;
	int blink_max_frame;
};

void start_action_logic
(
	struct Input*,
	int*
);

void start_collision_detection();

void start_update_world();

void start_render
(
	struct Screen*,
	struct StartLayout*,
	struct Letter[]
);

#endif