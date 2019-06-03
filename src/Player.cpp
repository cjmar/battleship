#include "Player.h"
#include "TextureManager.h"
#include <iostream>
#include "Game.h"

Player::Player()
{
	shipsHitNum = 0;
	//Make the boats
	playerShips.push_back(Ship("Carrier", 5));
	TextureManager::getSpriteSrc(TextureManager::Carrier, playerShips.at(0).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rCarrier, playerShips.at(0).shipSpriteR);

	playerShips.push_back(Ship("Battleship", 4));
	TextureManager::getSpriteSrc(TextureManager::Battleship, playerShips.at(1).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rBattleship, playerShips.at(1).shipSpriteR);

	playerShips.push_back(Ship("Cruiser", 3));
	TextureManager::getSpriteSrc(TextureManager::Cruiser, playerShips.at(2).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rCruiser, playerShips.at(2).shipSpriteR);

	playerShips.push_back(Ship("Submarine", 3));
	TextureManager::getSpriteSrc(TextureManager::Submarine, playerShips.at(3).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rSubmarine, playerShips.at(3).shipSpriteR);

	playerShips.push_back(Ship("Destroyer", 3));
	TextureManager::getSpriteSrc(TextureManager::Destroyer, playerShips.at(4).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rDestroyer, playerShips.at(4).shipSpriteR);

	//Move them to starting position
	for (unsigned int i = 0; i < playerShips.size(); i++)
	{
		playerShips.at(i).shipSprite.destRect.x = (i * 32 + 15 * 32) + 4;
		playerShips.at(i).shipSprite.destRect.y = 320;
	}
}

Player::~Player() {}

void Player::update()
{

}

void Player::renderShips()
{
	for (Ship &s : playerShips)
	{
		s.render();
	}
}

//Returns which attack coords hit
std::vector<SDL_Rect> Player::checkForHits(std::vector<SDL_Rect> hits_in)
{
	std::vector<SDL_Rect> hits;
	for (SDL_Rect r : hits_in)
	{
		r.x *= 32;
		r.y *= 32;
		for (Ship &s : playerShips)
		{
			SDL_Rect r2 = s.getDest();

			if (Battleship::Game::rectCollide(r, r2)) //One of the guesses was a hit
			{
				hits.push_back(r);
				shipsHitNum++;
			}
		}
	}
	return hits;
}

std::vector<Mark>& Player::getMarks()
{
	return playerMarks;
}

std::vector<Ship>& Player::getShips()
{
	return playerShips;
}

/*	Axis aligned bounding box
	True = test on hitbox
	False = test on destrect

*/
bool Player::shipCollide(SDL_Rect rect1, int selected, bool useHitbox)
{
	SDL_Rect rect2;
	bool collide = false;
	for (unsigned int i = 0; i < playerShips.size(); i++)
	{
		if (i != selected)
		{
			if (useHitbox) rect2 = playerShips.at(i).getHitbox();
			else rect2 = playerShips.at(i).getDest();

			if (rect1.x < rect2.x + rect2.w &&
				rect1.x + rect1.w > rect2.x &&
				rect1.y < rect2.y + rect2.h &&
				rect1.y + rect1.h > rect2.y)
				collide = true;
		}
	}
	return collide;
}

bool Player::shipCollide(int selected, bool useHitbox)
{
	SDL_Rect rect1;
	SDL_Rect rect2;
	if(useHitbox) rect1 = playerShips.at(selected).getHitbox();
	else rect1 = playerShips.at(selected).getDest();
	int collideNum = 0;

	bool collide = false;
	for (unsigned int i = 0; i < playerShips.size(); i++)
	{
		if (i != selected)
		{
			if (useHitbox) rect2 = playerShips.at(i).getHitbox();
			else rect2 = playerShips.at(i).getDest();

			if (rect1.x < rect2.x + rect2.w &&
				rect1.x + rect1.w > rect2.x &&
				rect1.y < rect2.y + rect2.h &&
				rect1.y + rect1.h > rect2.y)
				collide = true;
			collideNum = i;
		}
	}

	return collide;
}

bool Player::shipsStillAlive()
{
	if (shipsHitNum == 17) return false;
	else return true;
}