#include "gameover.h"


void gameover_action_logic(
	struct Input* input,
	struct GameOverLayout* layout,
	struct Screen* screen,
	struct Ball* ball,
	struct Player players[2],
	struct PongLayout* pong_layout
)
{
	if (input->up.action_state)
	{
		
		layout->index -= 1;
		if (layout->index < 0)
		{
			layout->index = 0;
		}
	}
	else if (input->down.action_state)
	{
		layout->index += 1;
		if (layout->index <= GAMEOVER_TOTAL)
		{
			layout->index = GAMEOVER_TOTAL - 1;
		}
	}


	if (input->start.action_state)
	{
		if (layout->index == GAMEOVER_EXIT_YES)
		{
			screen->view_index = VIEW_GAME;
			reset_players(players, pong_layout);
			reset_ball_speed(ball, pong_layout);
		}
		else if (layout->index == GAMEOVER_EXIT_NO)
		{
			screen->exit = SDL_GAME_EXIT;
		}

	}
}

void gameover_collision_detection()
{}

void gameover_update_world()
{}

void gameover_render
(
	struct Screen* screen,
	struct GameOverLayout* layout,
	struct Letter letters[],
	struct Letter letters_selected[]
)
{
	int x = screen->rect.w / 2;
	int y = screen->rect.h / 4;

	// TITLE

	int text_width = 0;
	int text_height = 0;


	text_width = get_string_w(letters, layout->title);
	text_height = get_string_h(letters, layout->title);

	render_string(
		screen->renderer,
		x - text_width/2,
		y - text_height/2,
		letters,
		layout->title
	);

	// QUESTION

	y = 2 * screen->rect.h / 4;

	text_width = get_string_w(letters, layout->title);
	text_height = get_string_h(letters, layout->title);

	render_string(
		screen->renderer,
		x - text_width/2,
		y - text_height/2,
		letters,
		layout->question
	);

	// OPTIONS

	y = 3 * screen->rect.h / 4;
	for (int i = 0; i < GAMEOVER_TOTAL; i++)
	{
		y += text_height + layout->spacing;
		text_width = get_string_w(letters, layout->options[i]);
		text_height = get_string_h(letters, layout->options[i]);

		if (i == layout->index){
			render_string(
				screen->renderer,
				x - text_width/2,
				y - text_height/2,
				letters_selected,
				layout->options[i]
			);
		}
		else
		{
			render_string(
				screen->renderer,
				x - text_width/2,
				y - text_height/2,
				letters,
				layout->options[i]
			);
		}
	}
}