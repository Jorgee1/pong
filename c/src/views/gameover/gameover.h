#include <SDL.h>

#include "views/index.h"

#include "utils/sdl.h"
#include "input/input.h"
#include "charset/charset.h"
#include "views/pong/pong.h"

#ifndef GAMEOVER_H
#define GAMEOVER_H

enum GAMEOVER_OPTIONS
{
	GAMEOVER_EXIT_YES,
	GAMEOVER_EXIT_NO,
	GAMEOVER_TOTAL
};

struct GameOverLayout
{
	char* title;
	char* question;
	char* options[2];
	int index;
	int spacing;
};

void gameover_action_logic(
	struct Input*,
	struct GameOverLayout*,
	struct Screen*,
	struct Ball*,
	struct Player[2],
	struct PongLayout*
);

void gameover_collision_detection();

void gameover_update_world();

void gameover_render
(
	struct Screen*,
	struct GameOverLayout*,
	struct Letter[],
	struct Letter[]
);


#endif