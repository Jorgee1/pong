#include <SDL.h>

#include "views/index.h"

#include "utils/sdl.h"
#include "input/input.h"
#include "charset/charset.h"


#ifndef PONG_H
#define PONG_H

struct Player
{
	SDL_Rect box;
	SDL_Color color;
	int score;
	int speed;
	int max_speed;
};

struct Ball
{
	SDL_Rect box;
	SDL_Color color;
	int speed_x;
	int speed_y;
	int max_speed;
};


struct PongLayout
{
	int score_padding;
	int players_padding;
	SDL_Point line[2];

	SDL_Point player_start_position[2];
	SDL_Point ball_start_position;
};

void reset_players(struct Player[2], struct PongLayout*);
void reset_ball_speed(struct Ball*, struct PongLayout*);

void game_action_logic
(
	struct Input*,
	struct Player[],
	struct Ball*,
	int*
);

void game_collision_detection
(
	struct Player[],
	int,
	struct Ball*,
	struct Screen*,
	struct PongLayout*
);

void game_update_world
(
	struct Player[],
	int,
	struct Ball*,
	struct Screen*
);

void game_render
(
	struct Screen*,
	struct PongLayout*,
	struct Player[],
	int,
	struct Ball*,
	struct Letter[]
);


#endif