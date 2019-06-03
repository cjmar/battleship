#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include "SDL2/SDL.h"

/*	A scene owns all the assets being drawn to the screen

*/

class Scene
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void mouseDown(int, int, int) = 0;
	virtual void mouseUp(int, int, int) = 0;
	virtual void mouseMove(int, int) = 0;
	virtual void init() = 0;

	bool inHitBox(int x, int y, SDL_Rect box, float scaling)
	{
		bool isxHit = false;
		bool isyHit = false;

		if (x >= box.x * scaling && x < box.x * scaling + box.w * scaling) isxHit = true;
		if (y >= box.y * scaling && y < box.y * scaling + box.h * scaling) isyHit = true;

		return (isxHit && isyHit);
	}

};

#endif