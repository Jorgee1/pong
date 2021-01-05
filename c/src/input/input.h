#include <SDL.h>

#ifndef INPUT_H
#define INPUT_H

struct Button
{
	int key;
	int state;
	int action_state;
	int action_flag;
};

struct Input
{
	struct Button up;
	struct Button down;
	struct Button left;
	struct Button right;
	struct Button action;
	struct Button cancel;
	struct Button start;
};

void update_buttons(struct Button* buttons[], int size);

#endif