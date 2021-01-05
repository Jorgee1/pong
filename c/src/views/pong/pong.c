#include "pong.h"

void reset_players(struct Player players[2], struct PongLayout* layout)
{
	players[0].box.x = layout->player_start_position[0].x;
	players[0].box.y = layout->player_start_position[0].y;
	players[0].score = 0;

	players[1].box.x = layout->player_start_position[1].x;
	players[1].box.y = layout->player_start_position[1].y;
	players[1].score = 0;
}

void reset_ball_speed(struct Ball* ball, struct PongLayout* layout)
{
	ball->box.x = layout->ball_start_position.x;
	ball->box.y = layout->ball_start_position.y;

	if (rand() % 2) ball->speed_x = -ball->speed_x;
	if (rand() % 2) ball->speed_y = -ball->speed_y;
}


void game_action_logic
(
	struct Input* input,
	struct Player players[],
	struct Ball* ball,
	int* view_current
)
{
	if      (input->up.state)    players[0].speed = -players[0].max_speed;
	else if (input->down.state)  players[0].speed =  players[0].max_speed;
	else players[0].speed = 0;


	if (players[1].box.y > ball->box.y)      players[1].speed = -players[1].max_speed;
	else if (players[1].box.y + players[1].box.h < ball->box.y) players[1].speed = players[1].max_speed;

	if (input->start.action_state)
	{
		*view_current = VIEW_PAUSE;
	}
}

void game_collision_detection
(
	struct Player players[],
	int player_count,
	struct Ball* ball,
	struct Screen* screen,
	struct PongLayout* layout
)
{
	// Check player colitino against world
	for (int i = 0; i < player_count; ++i)
	{
		int future_y = players[i].box.y + players[i].speed;

		if (future_y < 0) players[i].speed = 0;

		if (future_y + players[i].box.h > screen->rect.h) players[i].speed = 0;
	}

	// Check player colitino against ball
	if (check_collition(players[0].box, ball->box)) ball->speed_x =  ball->max_speed;
	if (check_collition(players[1].box, ball->box)) ball->speed_x = -ball->max_speed;

	// Check ball colitino against top-bottom screen sides
	if (
		(ball->box.y + ball->speed_y > screen->rect.h - ball->box.h) ||
		(ball->box.y + ball->speed_y < screen->rect.y)
	)
	{
		ball->speed_y = -ball->speed_y;
	}

	// Check ball collition agains screen left-right screen sides
	if (!check_collition(screen->rect, ball->box))
	{
		if (ball->speed_x > 0) players[0].score += 1;
		else if (ball->speed_x < 0) players[1].score += 1;

		// Restart ball
		reset_ball_speed(ball, layout);
	}
}

void game_update_world
(
	struct Player players[],
	int player_count,
	struct Ball* ball,
	struct Screen* screen
)
{


	if ((players[0].score >= 5) || (players[1].score >= 5))
	{
		screen->view_index = VIEW_GAMEOVER;
	}

	for (int i = 0; i < player_count; i++)
	{
		players[i].box.y += players[i].speed;
	}

	ball->box.x += ball->speed_x;
	ball->box.y += ball->speed_y;

}

void game_render
(
	struct Screen* screen,
	struct PongLayout* layout,
	struct Player players[],
	int player_count,
	struct Ball* ball,
	struct Letter letters[]
)
{
	for (int i = 0; i < player_count; i++)
	{
		SDL_SetRenderDrawColor(
			screen->renderer,
			players[i].color.r,
			players[i].color.g,
			players[i].color.b,
			players[i].color.a
		);
		SDL_RenderFillRect(screen->renderer, &(players[i].box));
	}

	SDL_SetRenderDrawColor(
		screen->renderer,
		ball->color.r,
		ball->color.g,
		ball->color.b,
		ball->color.a
	);
	SDL_RenderFillRect(screen->renderer, &(ball->box));


	char score_buffer[10];
	int score_buffer_size = 0;

	sprintf(score_buffer, "%d", players[0].score);
	score_buffer_size = get_string_w(letters, score_buffer);
	render_string(
		screen->renderer,
		screen->rect.w/2 - score_buffer_size - layout->score_padding,
		layout->score_padding,
		letters,
		score_buffer
	);


	sprintf(score_buffer, "%d", players[1].score);
	render_string(
		screen->renderer,
		screen->rect.w/2 + layout->score_padding,
		layout->score_padding,
		letters,
		score_buffer
	);

	SDL_RenderDrawLine(
		screen->renderer,
		layout->line[0].x, layout->line[0].y,
		layout->line[1].x, layout->line[1].y
	);
}