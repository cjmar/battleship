#pragma once
#ifndef HITBOX_H
#define HITBOX_H

#include "SDL2/SDL.h"
#include "Sprite.h"

namespace Hitbox
{
	bool rectCollide(SDL_Rect&, SDL_Rect&);
	bool spriteCollide(Sprite&, Sprite&);
	bool rectClickHit(int, int, SDL_Rect, float);
}

#endif