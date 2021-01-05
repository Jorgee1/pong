#include "pause.h"

void pause_action_logic
(
	struct Input* input,
	struct PauseLayout* layout,
	struct Screen* screen
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
		if (layout->index <= PAUSE_TOTAL)
		{
			layout->index = PAUSE_TOTAL - 1;
		}
	}


	if (input->start.action_state)
	{
		if (layout->index == PAUSE_RESUME)
		{
			screen->view_index = VIEW_GAME;
		}
		else if (layout->index == PAUSE_EXIT)
		{
			screen->exit = SDL_GAME_EXIT;
		}

	}
}

void pause_collision_detection()
{}

void pause_update_world()
{}

void pause_render
(
	struct Screen* screen,
	struct PauseLayout* layout,
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

	// OPTIONS
	y = screen->rect.h / 2;
	for (int i = 0; i < PAUSE_TOTAL; i++)
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
