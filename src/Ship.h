#ifndef SHIP_H
#define SHIP_H

#include "SDL2/SDL.h"
#include <string>
#include "Sprite.h"

class Ship
{
public:
	Ship();
	Ship(std::string, int);

	void move(int, int);
	void render();
	void rotate();

	Sprite shipSprite;
	Sprite shipSpriteR;
	std::string getName();
	SDL_Rect getHitbox();
	SDL_Rect getDest();

private:
	int shipSize;
	std::string shipName;
	bool rotated;

};

#endif