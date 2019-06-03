#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <vector>
#include "Ship.h"

class AIPlayer
{
public:
	AIPlayer();
	~AIPlayer();

	void generateShipPositions();
	std::vector<SDL_Rect> generateAttackCoords(int);
	std::vector<SDL_Rect> getHits(std::vector<SDL_Rect>);
	void sendHits(std::vector<SDL_Rect>);
	bool shipsStillAlive();

	void devRender(bool, bool);

private:
	int WIDTH;
	int HEIGHT;
	bool positionsGenerated;

	int shipsHitNum; //16 hits means all ships are sunk

	bool hitCoordCheck(int, int);
	std::vector<Ship> aiShips; //Just need the destRect from these
	std::vector<SDL_Rect> blackX; //devRender uses this to draw a large X over the ai ships
	Sprite xMark;
	bool shipCollision(Ship &, Ship &);
	SDL_Rect seaArea;
	std::vector<bool> masterAttackCoords;	//places fired
	std::vector<bool> aiShipHits; //places hit
};

#endif