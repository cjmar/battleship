#include "EndScene.h"
#include "TextureManager.h"
#include "Game.h"
#include "SceneManager.h"
#include "Hitbox.h"
#include "Colors.h"

EndScene::EndScene(int won_in)
{
	gameWon = won_in;
	message = "Message not set";
	textScale = 1.5f;

	switch (gameWon)
	{
		case 0:
		message = " You won the game! ";
		textScale = 1.8f;
		break;

		case 1:
		message = " You lost the game! ";
		textScale = 1.8f;
		break;

		case 2:
		message = "The game was a draw!";
		textScale = 1.6f;
		break;
	}

	WIDTH = int(Battleship::Game::GAME_WIDTH / 32 / Battleship::Game::gameScale);
	HEIGHT = int(Battleship::Game::GAME_HEIGHT / 32 / Battleship::Game::gameScale);

	TextureManager::getSpriteSrc(TextureManager::Water, waterSprite);
	TextureManager::getSpriteSrc(TextureManager::ButtonBGRed, redButton);
	redButton.destRect.w = int(redButton.destRect.w *1.5);
	redButton.destRect.h = int(redButton.destRect.h * 1.5);
	redButton.destRect.y = 7 * 32;

	playBox = exitBox = redButton.destRect;
	playBox.x = redButton.destRect.x = 4 * 32 + 32;
	exitBox.x = (4 * 32 + 12 * 32) - redButton.destRect.w - 32;

	TextureManager::getSpriteSrc(TextureManager::x3TLEFT, LT);
	TextureManager::getSpriteSrc(TextureManager::x3LEFT, LM);
	TextureManager::getSpriteSrc(TextureManager::x3BLEFT, LB);

	TextureManager::getSpriteSrc(TextureManager::x3TMID, MT);
	TextureManager::getSpriteSrc(TextureManager::x3MID, MM);
	TextureManager::getSpriteSrc(TextureManager::x3BMID, MB);

	TextureManager::getSpriteSrc(TextureManager::x3TRIGHT, RT);
	TextureManager::getSpriteSrc(TextureManager::x3RIGHT, RM);
	TextureManager::getSpriteSrc(TextureManager::x3BRIGHT, RB);
}

EndScene::~EndScene()
{

}

void EndScene::update()
{
	waterSprite.update();
}

void EndScene::render()
{
	//Width  20
	//Height 16

	//Draw water
	for (int x = 0; x < WIDTH; x++)
	for (int y = 0; y < HEIGHT; y++)
	{
		waterSprite.destRect.x = x * 32;
		waterSprite.destRect.y = y * 32;
		TextureManager::Draw(waterSprite);
	}

	//Draw button background and game end text
	drawUIBox(4*32, 4*32, 12, 6);
	TextureManager::DrawText(message, Colors::BLACK, 4*32 + 14, 4*32 + 16, textScale);

	//Draw play again button
	redButton.destRect.x = playBox.x;
	TextureManager::Draw(redButton);
	TextureManager::DrawText("Play", Colors::MANGO, playBox.x + 47, playBox.y + 8, 1.2f);
	TextureManager::DrawText("Again", Colors::MANGO, playBox.x + 39, playBox.y + 32, 1.2f);

	//Draw exit button
	redButton.destRect.x = exitBox.x;
	TextureManager::Draw(redButton);
	TextureManager::DrawText("Exit", Colors::MANGO, exitBox.x + 38, exitBox.y + 12, 1.8f);
}

void EndScene::mouseDown(int x, int y , int button)
{

}

void EndScene::mouseUp(int x, int y , int button)
{
	//Play again button
	if (Hitbox::rectClickHit(x, y, playBox, Battleship::Game::gameScale))
	{
		SceneManager::getInstance()->startScene(SceneManager::TitleScreen);
	}
	//Exit game button
	if (Hitbox::rectClickHit(x, y, exitBox, Battleship::Game::gameScale))
	{
		Battleship::Game::quit();
	}
}

void EndScene::mouseMove(int x, int y)
{

}

void EndScene::init()
{

}


void EndScene::drawUIBox(int xStart, int yStart, int UIwidth, int UIheight)
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
