#include "Sprite.h"
#include <iostream>

Sprite::Sprite()
{
	currentIndex = 0;
	delayMilli = 0;
	frameNum = 0;
}

Sprite::Sprite(SDL_Rect r, int col, int row, int delay_in)
{
	setSprite(r, col, row, delay_in);
}

/*	src: Entire portion the sprite takes up (included frames for animated)
	col: Number of columns in src sprite (1 for ships)
	row: Number of rows in src sprite	 (1 for ships)
*/
void Sprite::setSprite(SDL_Rect src, int col, int row, int delay_in)
{
	setSprite(src, src, col, row, delay_in);
}

void Sprite::setSprite(SDL_Rect src, SDL_Rect hb, int col, int row, int delay_in)
{
	delayMilli = unsigned int(delay_in);
	hitbox = hb;

	for (int y = 0; y < row; y++)
	for (int x = 0; x < col; x++)
	{
		SDL_Rect rect = src;
		rect.x += x * 32;
		rect.y += y * 32;
		rect.w = src.w / col;
		rect.h = src.h / row;
		srcRect.push_back(rect);
		frameNum++;
	}

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = srcRect.at(0).w;
	destRect.h = srcRect.at(0).h;

	frameLast = SDL_GetTicks();
}

void Sprite::update()
{
	//delayMilli is the amount of milliseconds between frames in a sprite
	if (delayMilli != 0) // if it is an animated sprite
	{
		frameCurrent = SDL_GetTicks();
		if (frameCurrent - frameLast > delayMilli)
		{
			currentIndex++;
			if (currentIndex == frameNum)
			{
				currentIndex = 0;
			}
			frameLast = frameCurrent;
		}
	}
}
