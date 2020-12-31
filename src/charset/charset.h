#include <SDL.h>
#include <SDL_ttf.h>

#ifndef CHARSET_H
#define CHARSET_H

struct Letter
{
	char letter;
	SDL_Texture* texture;
	int h;
	int w;	
};

int get_string_w(struct Letter*, char[]);

int get_string_h(struct Letter*, char[]);

void create_charset(SDL_Renderer*, TTF_Font*, struct Letter[], int, SDL_Color);

void destroy_charset(struct Letter[], int);

void render_string(SDL_Renderer* renderer, int x, int y, struct Letter* letters, char word[]);

#endif
