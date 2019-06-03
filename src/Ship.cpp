#include "Ship.h"
#include "TextureManager.h"

Ship::Ship() 
{
	shipName = "Values not initialized";
	shipSize = 0;
	rotated = false;
};

Ship::Ship(std::string name_in, int size_in)
{
	shipName = name_in;
	shipSize = size_in;
	rotated = false;

}

void Ship::render()
{
	if(!rotated)
		TextureManager::Draw(shipSprite);

	else 
		TextureManager::Draw(shipSpriteR);
}

void Ship::move(int x_in, int y_in)
{
	shipSprite.destRect.x = shipSpriteR.destRect.x = x_in;
	shipSprite.destRect.y = shipSpriteR.destRect.y = y_in;
}

SDL_Rect Ship::getDest()
{
	if (!rotated)
		return shipSprite.destRect;

	else
		return shipSpriteR.destRect;
}

SDL_Rect Ship::getHitbox()
{
	SDL_Rect box = getDest();
	if (!rotated)
	{
		box.x += shipSprite.hitbox.x;
		box.y += shipSprite.hitbox.y;
		box.w += shipSprite.hitbox.w;
		box.h += shipSprite.hitbox.h;
	}
	else
	{
		box.x += shipSpriteR.hitbox.x;
		box.y += shipSpriteR.hitbox.y;
		box.w += shipSpriteR.hitbox.w;
		box.h += shipSpriteR.hitbox.h;
	}

	return box;
}

void Ship::rotate()
{
	rotated = !rotated;
}

std::string Ship::getName()
{
	return shipName;
}
