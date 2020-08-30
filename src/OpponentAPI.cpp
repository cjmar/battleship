#include "OpponentAPI.h"
#include <iostream>

OpponentAPI::OpponentAPI()
{
}

OpponentAPI::~OpponentAPI() {}

/*
void OpponentAPI::sendAttackCoords(std::vector<SDL_Rect> attackCoords_in)
{
	if (isAIPlayer)
	{
		
	}

	else
	{
		outGoingCoords.clear();
		outGoingCoords = attackCoords_in;
		std::cout << "LAN player not able to recieve coords";
	}
}
*/
std::vector<SDL_Rect> OpponentAPI::checkForHits(std::vector<SDL_Rect> hits_in)
{
	return bsAI.getHits(hits_in);
}

void OpponentAPI::sendHitCoords(std::vector<SDL_Rect> hits)
{
	bsAI.sendHits(hits);
}

std::vector<SDL_Rect> OpponentAPI::getAttackCoords(int rNum)
{
		return bsAI.generateAttackCoords(rNum);
}

void OpponentAPI::devRender(bool b1, bool b2)
{
	bsAI.devRender(b1, b2);
}

bool OpponentAPI::isReady()
{
	bsAI.generateShipPositions();
	return true;
}

bool OpponentAPI::shipsStillAlive()
{
	return bsAI.shipsStillAlive();

}
