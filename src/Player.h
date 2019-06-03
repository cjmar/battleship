#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Ship.h"

struct Mark
{
	bool isBlack;
	SDL_Rect markDest;
};

class Player
{
public:
	Player();
	~Player();
	
	void update();
	void renderShips();

	int shipsHitNum; //16 hits means all ships are sunk

	std::vector<Mark>& getMarks();
	std::vector<Ship>& getShips();
	bool shipCollide(int, bool);
	bool shipCollide(SDL_Rect, int, bool);
	std::vector<SDL_Rect> checkForHits(std::vector<SDL_Rect>);
	bool shipsStillAlive();

private:
	std::vector<Ship> playerShips;
	std::vector<Mark> playerMarks;
};

#endif