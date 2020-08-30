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
};

#endif