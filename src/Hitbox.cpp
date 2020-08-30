#include "Hitbox.h"

/*
	Aligned axis rectangle hitbox check
	*/
bool Hitbox::rectCollide(SDL_Rect& r1, SDL_Rect& r2)
{
	bool collide = false;

	if (r1.x < r2.x + r2.w &&
		r1.x + r1.w > r2.x &&
		r1.y < r2.y + r2.h &&
		r1.y + r1.h > r2.y)

		collide = true;

	return collide;
}

/*
	Just calls rectCollide on the sprites destination rectangle
*/
bool Hitbox::spriteCollide(Sprite& s1, Sprite& s2)
{

	return Hitbox::rectCollide(s1.destRect, s2.destRect);;
}

bool Hitbox::rectClickHit(int x, int y, SDL_Rect box, float scaling)
{
	bool isxHit = false;
	bool isyHit = false;

	if (x >= box.x * scaling && x < box.x * scaling + box.w * scaling) isxHit = true;
	if (y >= box.y * scaling && y < box.y * scaling + box.h * scaling) isyHit = true;

	return (isxHit && isyHit);
}