#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include <vector>

class Sprite
{
public:
	Sprite();
	Sprite(SDL_Rect, int, int, int);
	void setSprite(SDL_Rect, int, int, int);
	void setSprite(SDL_Rect, SDL_Rect, int, int, int);

	std::vector<SDL_Rect> srcRect;
	SDL_Rect destRect;
	SDL_Rect hitbox; //approximate hitbox based on visual

	//Animation
	int frameNum;		//number of frames
	int currentIndex;	//Current frame its on 
	unsigned int delayMilli;		//(0 for no animation)
	Uint32 frameLast;
	Uint32 frameCurrent;

	void update();
};

#endif