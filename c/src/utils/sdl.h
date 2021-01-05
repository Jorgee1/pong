#include <SDL.h>

#ifndef SDL_UTILS_H
#define SDL_UTILS_H

enum EXIT_SATE
{
	SDL_GAME_RUN,
	SDL_GAME_EXIT
};

struct Colors
{
	SDL_Color red;
	SDL_Color green;
	SDL_Color blue;
	SDL_Color white;
	SDL_Color black;
};

struct Screen
{
	char *name;
	int view_index;
	int exit;
	
	SDL_Rect rect;
	SDL_Color clear_color;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

int check_collition(SDL_Rect, SDL_Rect);

#endif
