#ifndef OPPONENT_API
#define OPPONENT_API

#include <vector>
#include "AIPlayer.h"

/*
	Makes an AI agent or connects over LAN based on selection

	Gamescene calls a few functions to get information, API handles the rest (calling AI or sending/recieving information)

	std::pair<int, int>
	attack coords
	{
		pair<round, timesFired>
		pair<x, y>
		...
	}


*/

class OpponentAPI
{
public:
	OpponentAPI();
	~OpponentAPI();

	//void sendAttackCoords(std::vector<SDL_Rect>);
	void sendHitCoords(std::vector<SDL_Rect>);
	std::vector<SDL_Rect> checkForHits(std::vector<SDL_Rect>);
	std::vector<SDL_Rect> getAttackCoords(int);
	bool isReady();
	bool shipsStillAlive();

	void devRender(bool, bool);
private:
	std::vector<SDL_Rect> inComingCoords;
	std::vector<SDL_Rect> outGoingCoords;

	AIPlayer bsAI;
};

#endif