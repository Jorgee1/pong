#include "start.h"


void start_action_logic
(
	struct Input* input,
	int* view_current
)
{
	if (input->start.action_state)
	{
		*view_current = VIEW_GAME;
	}
}

void start_collision_detection()
{}

void start_update_world(struct StartLayout* layout)
{
	layout->blink_frame_count += 1;

	if (layout->blink_frame_count > layout->blink_max_frame)
	{
		layout->blink_frame_count = 0;

		if (layout->blink_flag)
		{
			layout->blink_flag = 0;
		}
		else
		{
			layout->blink_flag =  1;
		}
	}
}

void start_render
(
	struct Screen* screen,
	struct StartLayout* layout,
	struct Letter letters[]
)
{
	int x = screen->rect.w/2;
	int y = screen->rect.h/4;


	render_string(
		screen->renderer,
		x - get_string_w(letters, layout->title)/2,
		y,
		letters,
		layout->title
	);

	y = 2*screen->rect.h/3;

	if (layout->blink_flag)
	{
		render_string(
			screen->renderer,
			x - get_string_w(letters, layout->message)/2,
			y,
			letters,
			layout->message
		);
	}



}