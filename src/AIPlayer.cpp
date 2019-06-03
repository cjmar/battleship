#include "AIPlayer.h"
#include "TextureManager.h"
#include <time.h>
#include <iostream>
#include "Game.h"

AIPlayer::AIPlayer()
{
	shipsHitNum = 0;
	srand(time(NULL));

	//sea area is a 15x15 grid. The y is scaled to not include the topmost grid when seaArea is used
	seaArea = { 0, 32, 15 * 32, 16 * 32 }; 
	HEIGHT = 15;
	WIDTH = 15;

	positionsGenerated = false;
	TextureManager::getSpriteSrc(TextureManager::BlackX, xMark);

	//Make the boats
	aiShips.push_back(Ship("Carrier", 5));
	TextureManager::getSpriteSrc(TextureManager::Carrier, aiShips.at(0).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rCarrier, aiShips.at(0).shipSpriteR);

	aiShips.push_back(Ship("Battleship", 4));
	TextureManager::getSpriteSrc(TextureManager::Battleship, aiShips.at(1).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rBattleship, aiShips.at(1).shipSpriteR);

	aiShips.push_back(Ship("Cruiser", 3));
	TextureManager::getSpriteSrc(TextureManager::Cruiser, aiShips.at(2).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rCruiser, aiShips.at(2).shipSpriteR);

	aiShips.push_back(Ship("Submarine", 3));
	TextureManager::getSpriteSrc(TextureManager::Submarine, aiShips.at(3).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rSubmarine, aiShips.at(3).shipSpriteR);

	aiShips.push_back(Ship("Destroyer", 3));
	TextureManager::getSpriteSrc(TextureManager::Destroyer, aiShips.at(4).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rDestroyer, aiShips.at(4).shipSpriteR);

	//Move them to starting position
	for (unsigned int i = 0; i < aiShips.size(); i++)
	{
		aiShips.at(i).shipSprite.destRect.x = 32 * i;
		aiShips.at(i).shipSprite.destRect.y = 32;

		blackX.push_back(aiShips.at(i).getDest());
	}

	for (int x = 0; x < WIDTH * HEIGHT; x++)
	{
		masterAttackCoords.push_back(false);
		aiShipHits.push_back(false);
	}
}

AIPlayer::~AIPlayer()
{

}

void AIPlayer::generateShipPositions()
{
	if (!positionsGenerated)
	{
		bool collision = false;
		int currentIndex = 0;

		//For each ship
		for (Ship& s : aiShips)
		{
			//Get x, y coords for it
			do
			{
				collision = false;
				int xPos = rand() % (15);
				int yPos = rand() % (15 - 2) + 1;

				xPos *= 32;
				yPos *= 32;

				//Figure out a rotation for it
				if (rand() % 2)
				{
					s.rotate();
				}

				//Ship sticking out of right side
				if (xPos + s.getDest().w > seaArea.w) xPos = seaArea.w - s.getDest().w;

				//Ship sticking out of bottom
				if (yPos + s.getDest().h > seaArea.h) yPos = seaArea.h - s.getDest().h + 1;

				s.move(xPos, yPos);

				//Check if the coords make it overlap another ship
				int i = 0;
				for (Ship& s : aiShips)
				{
					//If there is an overlap, set collision to true
					if (shipCollision(aiShips.at(i), aiShips.at(currentIndex)) && currentIndex != i)
					{
						collision = true;
					}
					//If it is outside the sea area, move it

					i++;
				}

			} while (collision);

			currentIndex++;
		}
		positionsGenerated = true;
	}
}

bool AIPlayer::shipCollision(Ship &s1, Ship &s2)
{
	bool collision = false;
	SDL_Rect rect1 = s1.getDest();
	SDL_Rect rect2 = s2.getDest();

	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		rect1.y + rect1.h > rect2.y)
		collision = true;

	return collision;
}

/*
	Currently based purely on RNG
	Eventually group the shots around hits 
*/
std::vector<SDL_Rect> AIPlayer::generateAttackCoords(int rNum)
{
	std::vector<std::pair<int, int>> coordSet; //Vector holding 5 corrdinates to use on round
	std::vector<std::pair<int, int>> pairList; //Vector of all coordinates not used yet
	int shotsFired = 0;

	//Iterate through all the squares
	for (int x = 0; x < WIDTH; x++)
	for (int y = 0; y < HEIGHT; y++)
	{
		int index = y + HEIGHT * x; //index of mastercoord
		bool fired = false;
		std::pair<int, int> coord = std::make_pair(x, y);

		//Check
		if (!masterAttackCoords.at(index)) //If this point has not been fired upon yet
		{
			/*	Look at the four spots in cardinal direction around this point
				If any are hits, then fire on this position
			*/
			//Top
			if (hitCoordCheck(x, y - 1) && shotsFired < 5)
			{
				coordSet.push_back(coord);
				shotsFired++;
				masterAttackCoords.at(index) = true;
				fired = true;
			}
			//Left
			else if (hitCoordCheck(x - 1, y) && shotsFired < 5)
			{
				coordSet.push_back(coord);
				shotsFired++;
				masterAttackCoords.at(index) = true;
				fired = true;
			}
			//Bottom
			else if (hitCoordCheck(x, y + 1) && shotsFired < 5)
			{
				coordSet.push_back(coord);
				shotsFired++;
				masterAttackCoords.at(index) = true;
				fired = true;
			}
			//Right
			else if (hitCoordCheck(x + 1, y) && shotsFired < 5)
			{
				coordSet.push_back(coord);
				shotsFired++;
				masterAttackCoords.at(index) = true;
				fired = true;
			}
			//Else add the point to pairList for random selection
			else if (!fired) //If this point has not been fired on yet
			{
				pairList.push_back(coord);
			}
		}
	}
	
	//Generate random indexes using the pairList vector
	for (int i = shotsFired; i < 5; i++) //How many shots there are
	{
		int randInt = 0;

		if (pairList.size() != 0)
		{
			//Pick random coord from list
			randInt = rand() % pairList.size();

			int index = pairList.at(randInt).second + HEIGHT * pairList.at(randInt).first;
#if _DEBUG
			if (masterAttackCoords.at(index)) std::cout << "AIPlayer::GenerateAttackCoords->MasterAttackCoords tried to set true=true\n";
#endif
			masterAttackCoords.at(index) = true;

			coordSet.push_back(pairList.at(randInt));
			pairList.erase(pairList.begin() + randInt);
		}
	}
	
	//Convert the coords into a SDL_Rect
	std::vector<SDL_Rect> convertedCoords;

	for (std::pair<int, int> c : coordSet)
	{
		SDL_Rect r = {c.first, c.second + 1, 32, 32};
		convertedCoords.push_back(r);
	}

	//Print the coordinates for debug
#if _DEBUG
	std::cout << "rr\n";
	for (SDL_Rect r : convertedCoords)
	{
		Battleship::Game::printRect(r);
	}
#endif

	return convertedCoords;
}

bool AIPlayer::hitCoordCheck(int x, int y)
{
	bool hit = false;
	y++;
	int index = y + HEIGHT * x;
	bool inBounds = (index >= 0 && index < aiShipHits.size() - 1);
	if (inBounds && aiShipHits.at(index)) //if this square was a hit
	{
		hit = true;
		std::cout << x << ", " << y << "  is a hit\n";
	}

	return hit;
}

void AIPlayer::sendHits(std::vector<SDL_Rect> hits_in)
{
	for (SDL_Rect r : hits_in)
	{
		int x = r.x / 32;
		int y = r.y / 32;
		int index = y + HEIGHT * x;
		aiShipHits.at(index) = true;
	}
}

std::vector<SDL_Rect> AIPlayer::getHits(std::vector<SDL_Rect> hits_in)
{
	std::vector<SDL_Rect> hits;
	for (SDL_Rect r : hits_in)
	{
		for (Ship& s : aiShips)
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

void AIPlayer::devRender(bool showShips, bool showMarks)
{
	if(showMarks)
	for(int x = 0; x < WIDTH; x++)
	for(int y = 0; y < HEIGHT; y++)
	{
		int index = y + HEIGHT * x; //index of mastercoord

		if (masterAttackCoords.at(index))
		{
			xMark.destRect.x = x * 32;
			xMark.destRect.y = (y * 32) + 32;
			TextureManager::Draw(xMark);
		}
	}

	if(showShips)
	for (Ship &s : aiShips)
	{
		s.render();

		xMark.destRect = s.getDest();
		TextureManager::Draw(xMark);
	}
	xMark.destRect.w = 16;
	xMark.destRect.h = 16;
}

bool AIPlayer::shipsStillAlive()
{
	if (shipsHitNum == 17) return false;
	else return true;
}