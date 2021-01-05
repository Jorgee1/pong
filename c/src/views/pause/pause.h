#include <SDL.h>

#include "views/index.h"

#include "utils/sdl.h"
#include "input/input.h"
#include "charset/charset.h"


#ifndef PAUSE_H
#define PAUSE_H

enum PAUSE_OPTIONS
{
	PAUSE_RESUME,
	PAUSE_EXIT,
	PAUSE_TOTAL
};

struct PauseLayout
{
	char* title;
	char* options[2];
	int index;
	int spacing;
};

void pause_action_logic(
	struct Input*,
	struct PauseLayout*,
	struct Screen*
);

void pause_collision_detection();

void pause_update_world();

void pause_render
(
	struct Screen*,
	struct PauseLayout*,
	struct Letter[],
	struct Letter[]
);

#endif

