#include "GameScene.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include <cmath>

GameScene::GameScene(bool AI, OpponentAPI * p2API)
{
	p2 = p2API;
	p2Message = "Welcome to Battleship";
	roundNum = 0;
	vsAI = true;

	if (!vsAI) p2 = { false };

	delayTime = 60;
	delayCurrent = 0;
	gameWon = 0;

	shipOnMouse = false;
	markOnMouse = false;
	shipsLocked = false;
	marksLocked = false;
	selected = 0;
	seaArea = {0, 32, 15 * 32, 16 * 32};

	TextureManager::getSpriteSrc(TextureManager::Water, waterSprite);
	TextureManager::getSpriteSrc(TextureManager::Paper, paperSprite);
	TextureManager::getSpriteSrc(TextureManager::Shell, shellSprite);
	TextureManager::getSpriteSrc(TextureManager::BlackX, blackMark);
	TextureManager::getSpriteSrc(TextureManager::RedO, redMark);
	TextureManager::getSpriteSrc(TextureManager::Flag, flagSprite);

	TextureManager::getSpriteSrc(TextureManager::MetalPanelDark, metalPanel);
	TextureManager::getSpriteSrc(TextureManager::TitleText, titleText);
	TextureManager::getSpriteSrc(TextureManager::ButtonBGRed, lockButton);

	TextureManager::getSpriteSrc(TextureManager::x3TLEFT, LT);
	TextureManager::getSpriteSrc(TextureManager::x3LEFT, LM);
	TextureManager::getSpriteSrc(TextureManager::x3BLEFT, LB);

	TextureManager::getSpriteSrc(TextureManager::x3TMID, MT);
	TextureManager::getSpriteSrc(TextureManager::x3MID, MM);
	TextureManager::getSpriteSrc(TextureManager::x3BMID, MB);

	TextureManager::getSpriteSrc(TextureManager::x3TRIGHT, RT);
	TextureManager::getSpriteSrc(TextureManager::x3RIGHT, RM);
	TextureManager::getSpriteSrc(TextureManager::x3BRIGHT, RB);

	lockButton.destRect.x = 32 * 16;
	lockButton.destRect.y = 32 * 8 + 8;

	titleText.destRect.x = 2 * titleText.destRect.w - titleText.destRect.w / 2;
	currentState = SettingUp;
}

GameScene::~GameScene()
{
	
}

void GameScene::init()
{


	delayCurrent = 0;

	shipOnMouse = false;
	markOnMouse = false;
	shipsLocked = false;
	marksLocked = false;
	selected = 0;

	if (vsAI) p2->init();
}

void GameScene::update()
{
	//update water sprites
	waterSprite.update();

	for (Sprite& s : smoke)
		s.update();

	for (Sprite& s : explosions)
		s.update();

	for (Sprite& s : splashes)
		s.update();

	flagSprite.update();
}

void GameScene::render()
{
	drawUI();

	//Scene specific drawing
	switch (currentState)
	{
	case SettingUp:
		if (!shipsLocked)
			TextureManager::DrawText("LOCK", Battleship::MANGO, lockButton.destRect.x + 11, lockButton.destRect.y + 7, 1.3);

		drawWater();
		break;

	case OnGoing:
		if(!marksLocked)
			TextureManager::DrawText("LOCK", Battleship::MANGO, lockButton.destRect.x + 11, lockButton.destRect.y + 7, 1.3);

		if(marksLocked)
			TextureManager::DrawText("LOCKED", Battleship::MANGO, lockButton.destRect.x + 11, lockButton.destRect.y + 11, 0.9);

		drawPaper();
		drawMarks();
		break;

	case PlayAnim:
		TextureManager::DrawText("LOCKED", Battleship::MANGO, lockButton.destRect.x + 11, lockButton.destRect.y + 11, 0.9);
		drawWater();
		firingPhase();
		break;

	case GameEnd:
		SceneManager::getInstance()->setGameWon(gameWon);
		SceneManager::getInstance()->startScene(SceneManager::GameEnd);
		break;
	}

//showShips, showMarks
#if _DEBUG
	p2->devRender(false, true);
#endif
}

void GameScene::drawUI()
{
	//draw horzontal panel UI peices

	metalPanel.destRect.y = 0;
	for (unsigned int i = 0; i < 15; i++)
	{
		metalPanel.destRect.x = i * 32;
		TextureManager::Draw(metalPanel);
	}

	
	//draw right panel UI background
	for (unsigned int x = 15; x < 20; x++)
	for (unsigned int y = 0; y < 16; y++)
	{
		metalPanel.destRect.x = x * 32;
		metalPanel.destRect.y = y * 32;
		TextureManager::Draw(metalPanel);
	}

	//Draw the message box and messages
	drawUIBox(15 * 32, 1 * 32 + 8, 5, 7);
	drawUIBox(15 * 32, 10 * 32 - 8, 5, 6);

	TextureManager::DrawText(p2Message.c_str(), Battleship::BLACK, 15 * 32 + 12, 1 * 32 + 12, 0.5);

	//draw title
	TextureManager::Draw(titleText);
	//Draw lock button and text
	TextureManager::Draw(lockButton);

}

void GameScene::drawUIBox(int xStart, int yStart, int UIwidth, int UIheight)
{
	//Draw Tiled UI background
	for (int x = 0; x < UIwidth; x++)
	for (int y = 0; y < UIheight; y++)
	{
		int xPos = xStart + x * 32;
		int yPos = yStart + y * 32;

		//Corners
		if ((x == 0) && (y == 0))
		{
			LT.destRect.x = xPos;
			LT.destRect.y = yPos;
			TextureManager::Draw(LT);
		}
		else if (x == 0 && y == UIheight - 1)
		{
			LB.destRect.x = xPos;
			LB.destRect.y = yPos;
			TextureManager::Draw(LB);
		}
		else if (x == UIwidth - 1 && y == 0)
		{
			RT.destRect.x = xPos;
			RT.destRect.y = yPos;
			TextureManager::Draw(RT);
		}
		else if (x == UIwidth - 1 && y == UIheight - 1)
		{
			RB.destRect.x = xPos;
			RB.destRect.y = yPos;
			TextureManager::Draw(RB);
		}
		//Edges
		else if (y == 0)
		{
			MT.destRect.x = xPos;
			MT.destRect.y = yPos;
			TextureManager::Draw(MT);
		}
		else if (y == UIheight - 1)
		{
			MB.destRect.x = xPos;
			MB.destRect.y = yPos;
			TextureManager::Draw(MB);
		}
		else if (x == 0)
		{
			LM.destRect.x = xPos;
			LM.destRect.y = yPos;
			TextureManager::Draw(LM);
		}
		else if (x == UIwidth - 1)
		{
			RM.destRect.x = xPos;
			RM.destRect.y = yPos;
			TextureManager::Draw(RM);
		}
		else
		{
			MM.destRect.x = xPos;
			MM.destRect.y = yPos;
			TextureManager::Draw(MM);
		}
	}
}

void GameScene::mouseDown(int x, int y, int button)
{

}

void GameScene::mouseUp(int x, int y, int button)
{

	if (inHitBox(x, y, lockButton.destRect, Battleship::Game::gameScale))
	{
		lockButtonEvent();
	}

	if (!shipsLocked)
	{
		shipClickEvent(x, y, button);
	}
	
	if(!marksLocked)
	{
		markClickEvent(x, y, button);
	}
	//Dev button in very top left corner
#if _DEBUG
	if (x < (32 * Battleship::Game::gameScale) && y < (32 * Battleship::Game::gameScale))
	{
		devButtonEvent();
	}
#endif
}

void GameScene::mouseMove(int x, int y) 
{
	if (shipOnMouse)
	{
		p1.getShips().at(selected).move(x - 16, y - 16);
	}

	if(markOnMouse)
	{
		newMarks.at(selected).x = x - 16;
		newMarks.at(selected).y = y - 16;
	}
} 

bool GameScene::lockSelectedToGrid(int x, int y) 
{
	int xPos = round(x / 32 / Battleship::Game::gameScale) * 32;
	int yPos = round(y / 32 / Battleship::Game::gameScale) * 32;

	//Bounds check xPos and yPos
	if (xPos < seaArea.x || xPos > seaArea.w) xPos = seaArea.x;
	if (yPos < seaArea.y) yPos = seaArea.y;
	else if (yPos > seaArea.h)
	{
		yPos = seaArea.h;
	}

	int width = p1.getShips().at(selected).getDest().w;
	int height = p1.getShips().at(selected).getDest().h;

	//Ship sticking out of right side
	if (xPos + width > seaArea.w) xPos = seaArea.w - width;

	//Ship sticking out of bottom
	if (yPos + height > seaArea.h) yPos = seaArea.h - height + 1;

	//Finally move the ship
	bool validPlacement = false;
	SDL_Rect temp = { xPos, yPos, p1.getShips().at(selected).getDest().w,  p1.getShips().at(selected).getDest().h };

	if (!p1.shipCollide(temp, selected, false))
	{
		p1.getShips().at(selected).move(xPos, yPos);
		validPlacement = true;
	}
	return validPlacement;
}

void GameScene::lockButtonEvent()
{
	switch (currentState)
	{
	case SettingUp: //lock in ships
		setupPhase();
		break;

	case OnGoing:   //main game loop
		markingPhase();
		break;

	case GameEnd:	//Winner is chosen, change scene to gameEnd
		break;
	}
}


void GameScene::devButtonEvent()
{
	currentState = GameEnd;
	gameWon = 1;
}

void GameScene::createFiveNewMarks()
{
	for (int i = 0; i < 5; i++)
	{
		SDL_Rect markRect = {17*32, 10*32 + i*32, 32, 32};
		newMarks.push_back(markRect);
	}
}

void GameScene::markingPhase()
{
	if (!marksLocked)
	{
		bool good[] = { false, false, false, false, false };
		int i = 0;

		for (SDL_Rect m : newMarks)
		{
			bool markPlaced = false;
			bool xGood = false;
			bool yGood = false;

			if (m.x < seaArea.w) xGood = true;
			if (m.y < seaArea.h) yGood = true;

			if (xGood && yGood) markPlaced = true;

			good[i] = markPlaced;
			i++;
		}

		marksLocked = (((good[0] && good[1]) && (good[2] && good[3])) && good[4]);

		if(marksLocked)
		{
			//Wait for the other player
			if (p2->isReady())
			{
				//Checks for hits are to the perspective of the player, not AI or LANed player
				//Check for defensive hits
				p2Marks = p2->getAttackCoords(roundNum);
				successDefHits = p1.checkForHits(p2Marks);
				p2->sendHitCoords(successDefHits);
				//Set up the marks for the animation
				for (SDL_Rect &r : p2Marks)
				{
					//Use w, h as the target location {xPos, yPos, xTar, yTar }
					r.w = r.x;
					r.h = r.y;

					//Use x, y as the current location while the animation plays
					r.y = 0;
				}

				//Check for offensive hits
				successOffHits = p2->checkForHits(newMarks);

				//Add successful hits so they're printed differently
				for (SDL_Rect r : successOffHits)
				{
					Mark m;
					m.isBlack = false;
					m.markDest = r;
					p1.getMarks().push_back(m);
				}
				//Add the rest
				for (SDL_Rect nM : newMarks)
				{
					bool collision = false;
					for (SDL_Rect r : successOffHits)
					{
						if (Battleship::Game::rectCollide(nM, r))
						{
							collision = true;
						}
					}
					if (!collision)
					{
						Mark m;
						m.isBlack = true;
						m.markDest = nM;
						p1.getMarks().push_back(m);
					}
				}

				//Play the firing animations
				currentState = PlayAnim;

			}
		}
	}
}

void GameScene::firingPhase()
{
	bool done = true;
	int i = 0;
	//Draw shells at deffensive hit positions
	for (SDL_Rect &r : p2Marks)
	{
		if (r.y <= r.h * 32) //if it hasnt yet reached its destination
		{
			shellSprite.destRect.x = r.x * 32;
			shellSprite.destRect.y = r.y;
			TextureManager::Draw(shellSprite);
			//Update them until they reach their target
			r.y += 2;
			done = false;

			if (r.y >= r.h * 32) //if reaching destination after update then add a new explosion
			{
				//Give it a splash animation when it reaches the end
				Sprite spl;
				TextureManager::getSpriteSrc(TextureManager::Splash, spl);
				spl.destRect.x = r.x * 32;
				spl.destRect.y = r.y;

				//Set up explosions on the shells that hit
				for (SDL_Rect r1 : successDefHits)
				{
					//Unmess the shell 
					SDL_Rect r2 = {r.x * 32, r.y, 32, 32};
					if (Battleship::Game::rectCollide(r2, r1)) //Collides with the ship
					{
						Sprite ex;
						TextureManager::getSpriteSrc(TextureManager::Explosion, ex);
						ex.destRect.x = r.x * 32;
						ex.destRect.y = r.y;

						//Hide the splash sprite
						spl.destRect.x = -100;
						spl.destRect.y = -100;

						explosions.push_back(ex);
					}
				}

				splashes.push_back(spl);
			}
		}
		i++;
	}
	//Check for end of explosions
	for (Sprite &s : explosions)
	{
		TextureManager::Draw(s);
		if ((s.currentIndex == s.frameNum - 1) && s.destRect.x != -100) //The explosion animation has ended
		{
			done = false;
			Sprite sm;
			TextureManager::getSpriteSrc(TextureManager::Smoke, sm);
			sm.destRect.x = s.destRect.x;
			sm.destRect.y = s.destRect.y;
			smoke.push_back(sm);

			s.destRect.x = -100;
			s.destRect.y = -100;
		}
	}
	//Check for end of splashes
	for (Sprite &s : splashes)
	{
		TextureManager::Draw(s);
		if ((s.currentIndex == s.frameNum - 1) && s.destRect.x != -100) //The explosion animation has ended
		{
			done = false;

			s.destRect.x = -100;
			s.destRect.y = -100;
		}
	}

	//Check for round end when firing finishes
	if (done)
	{
		delayCurrent++;

		if (!p2->shipsStillAlive())
		{
			gameWon = 0;
			currentState = GameEnd;
		}

		if (!p1.shipsStillAlive())
		{
			gameWon = 1;
			currentState = GameEnd;
		}

		if (!p2->shipsStillAlive() && !p1.shipsStillAlive())
		{
			gameWon = 2;
			currentState = GameEnd;
		}
	}
	if (delayCurrent >= delayTime)
	{
		delayCurrent = 0;
		p2Marks.clear();
		newMarks.clear();
		explosions.clear();
		splashes.clear();
		currentState = OnGoing;
		marksLocked = false;
		createFiveNewMarks();
	}
}

void GameScene::setupPhase()
{
	if(!shipsLocked)
	{
		bool good[] = {false, false, false, false, false};
		int i = 0;

		for (Ship &s : p1.getShips())
		{
			bool shipPlaced = false;
			bool xGood = false;
			bool yGood = false;

			if (s.getDest().x < seaArea.w) xGood = true;
			if (s.getDest().y < seaArea.h) yGood = true;

			if (xGood && yGood) shipPlaced = true;

			good[i] = shipPlaced;
			i++;
		}

		shipsLocked = (((good[0] && good[1]) && (good[2] && good[3])) && good[4]);

		if (shipsLocked)
		{
			//Wait for other player update
			if (p2->isReady())
			{
				//Display a message based on the other player
				p2Message = "TEST MESSAGE";

				//Change state once other player locked
				currentState = OnGoing;
				createFiveNewMarks();
			}
		}
	}
}

//Follows same logic as the shipClickEvent
void GameScene::markClickEvent(int x, int y, int button)
{
	bool startMark = markOnMouse;

	if (!markOnMouse)
	{
		int i = 0;
		for (SDL_Rect& m : newMarks)
		{
			//See if one of the new marks was clicked on
			if (inHitBox(x, y, m, Battleship::Game::gameScale))
			{
				markOnMouse = !markOnMouse;
				selected = i;

				newMarks.at(i).x = int(Battleship::Game::mouseX / Battleship::Game::gameScale - 16);
				newMarks.at(i).y = int(Battleship::Game::mouseY / Battleship::Game::gameScale - 16);
			}
			i++;
		}
	}
	else //There is a mark on the mouse
	{
		//If x, y is in the seaArea
		if (inHitBox(x, y, seaArea, Battleship::Game::gameScale))
		{
			//Check for a collision with other marks
			bool collision = false;
			for (Mark& m : p1.getMarks())
			{
				SDL_Rect r = m.markDest;
				//Makes sure the x, y is in an unused place
				if(inHitBox(x, y, r, Battleship::Game::gameScale))
				{
					collision = true;
				}
			}
			//Check against other new marks being made
			for (int i = 0; i < newMarks.size(); i++)
			{
				if (i != selected) //dont check it against itself
				{
					//Makes sure you clicked on an unused spot on the map
					if(inHitBox(x, y, newMarks.at(i), Battleship::Game::gameScale))
					{
						collision = true;
					}
					if (!collision)
					{
						//Simulate the mark being put down
						int xPos = floor(x / 32 / Battleship::Game::gameScale) * 32;
						int yPos = round(y / 32 / Battleship::Game::gameScale) * 32;

						SDL_Rect sim = {xPos, yPos, 32, 32};

						//See if the simulated collides with the other new marks
						if (Battleship::Game::rectCollide(sim, newMarks.at(i)))
							collision = true;

						//See if the simulated collides with other marks
						for (SDL_Rect& r : successOffHits)
						{
							if (Battleship::Game::rectCollide(sim, r))
								collision = true;
						}

						//See if the simulated collides with other marks
						for (Mark& m : p1.getMarks())
						{
							SDL_Rect r = m.markDest;
							if (Battleship::Game::rectCollide(sim, r))
								collision = true;
						}

						//Make sure the generated coords are within the seaArea
						if (!Battleship::Game::rectCollide(sim, seaArea))
							collision = true;
					}
				}
			}
			//Place the mark
			if (!collision)
			{
				markOnMouse = !markOnMouse;
				int xPos = floor(x / 32 / Battleship::Game::gameScale) * 32;
				int yPos = round(y / 32 / Battleship::Game::gameScale) * 32;

				newMarks.at(selected).x = xPos;
				newMarks.at(selected).y = yPos;
			}
		}
	}
}

void GameScene::shipClickEvent(int x, int y, int button)
{
	//Remember if ship was on mouse at start of method
	bool startShip = shipOnMouse;

	//If there is no ship on mouse, see if anything was clicked
	if (!shipOnMouse)
	{
		int i = 0;
		for (Ship& s : p1.getShips())
		{
			if (inHitBox(x, y, s.getDest(), Battleship::Game::gameScale))
			{
				shipOnMouse = !shipOnMouse;
				selected = i;
				p1.getShips().at(selected).move(int(Battleship::Game::mouseX / Battleship::Game::gameScale - 16),
					int(Battleship::Game::mouseY / Battleship::Game::gameScale - 16));
			}
			i++;
		}
	}

	else //There is a ship on the mouse 
	{
		switch (button)
		{
		case SDL_BUTTON_LEFT:
			if (inHitBox(x, y, seaArea, Battleship::Game::gameScale))
			{
				//Lock it to the screen if it doesnt hit another ship
				if (!p1.shipCollide(selected, true))
				{
					if (lockSelectedToGrid(x, y))
						if (startShip) shipOnMouse = !shipOnMouse;
				}
			}
			break;

		case SDL_BUTTON_RIGHT:
			p1.getShips().at(selected).rotate();
			break;
		}
	}
}

void GameScene::drawWater()
{
	//draw water over the map
	for (int x = 0; x < 15; x++)
	for (int y = 1; y < 16; y++)
	{
		waterSprite.destRect.x = x * 32;
		waterSprite.destRect.y = y * 32;
		TextureManager::Draw(waterSprite);
	}
	p1.renderShips();
	//When water is draw, so is any smoke from hits
	for (Sprite &s : smoke)
	{
		TextureManager::Draw(s);
	}
}

void GameScene::drawPaper()
{
	//draw paper over the map
	for (int x = 0; x < 15; x++)
	for (int y = 1; y < 16; y++)
	{
		paperSprite.destRect.x = (x * 32) - 32;
		paperSprite.destRect.y = y * 32;
		TextureManager::Draw(paperSprite);
	}
}

void GameScene::drawMarks()
{
	for (Mark m : p1.getMarks())
	{
		if (m.isBlack)
		{
			blackMark.destRect.x = m.markDest.x;
			blackMark.destRect.y = m.markDest.y;
			TextureManager::Draw(blackMark);
		}
		else if (!m.isBlack)
		{
			redMark.destRect.x = m.markDest.x;
			redMark.destRect.y = m.markDest.y;
			TextureManager::Draw(redMark);
		}
	}
	
	for(SDL_Rect mark : newMarks)
	{
		flagSprite.destRect.x = mark.x;
		flagSprite.destRect.y = mark.y;

		TextureManager::Draw(flagSprite);
	}
}