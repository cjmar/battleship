#include "TitleScene.h"
#include "TextureManager.h"
#include "Game.h"
#include <cmath>
#include <ctime>
#include "Hitbox.h"
#include "Colors.h"

TitleScene::TitleScene()
{
	//Button locations
	PLAYbutton = { int(Battleship::Game::GAME_WIDTH / 4 + 16), 118, 1, 1};  //96
	EXITbutton = { int(Battleship::Game::GAME_WIDTH / 4 + 16), 224, 1, 1 };  //224

	seaArea = {0, 13*32, 20*32, 13*32};
	shellActive = false;
	shellCoords = {0, 0, 0, 0}; //where it is , where its going

	explosionActive = false;
	shellActive = false;
	splashActive = false;

	TextureManager::getSpriteSrc(TextureManager::ButtonBGBlack, buttonBG);
	TextureManager::getSpriteSrc(TextureManager::MetalPanelDark, metalPanelDark);
	TextureManager::getSpriteSrc(TextureManager::MetalPanelLight, metalPanelLight);

	TextureManager::getSpriteSrc(TextureManager::Water, waterSprite);
	TextureManager::getSpriteSrc(TextureManager::Explosion, explosionSprite);
	TextureManager::getSpriteSrc(TextureManager::TitleText, titleText);
	TextureManager::getSpriteSrc(TextureManager::Shell, shellSprite);
	TextureManager::getSpriteSrc(TextureManager::Splash, splashSprite);

	titleText.destRect.w *= 2;
	titleText.destRect.h *= 2;

	titleText.destRect.x = titleText.destRect.w - titleText.destRect.w / 2;
	titleText.destRect.y = 5;

	for (int i = 0; i < 5; i++)
	{
		boats.push_back(Ship());
	}

	TextureManager::getSpriteSrc(TextureManager::rBattleship, boats.at(0).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rCarrier, boats.at(1).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rSubmarine, boats.at(2).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rDestroyer, boats.at(3).shipSprite);
	TextureManager::getSpriteSrc(TextureManager::rCruiser, boats.at(4).shipSprite);

	boatX = 16 * 32;
	boatY = 14 * 32;
	selected = 0;

	for(Ship &s : boats)
		s.move(boatX, boatY);

	buttons.push_back(PLAYbutton);
	buttons.push_back(EXITbutton);

	for (SDL_Rect &s : buttons)
	{
		s.w = buttonBG.destRect.w;
		s.h = buttonBG.destRect.h;
	}
}

TitleScene::~TitleScene()
{
}

void TitleScene::init()
{
}

void TitleScene::update() 
{
	//update boat
	boatX -= 1;
	if (boatX < 0 - boats.at(selected).shipSprite.destRect.w)
	{
		srand(unsigned int(time(NULL)));
		selected = rand() % 4;
		boatX = 20 * 32;
	}
	boats.at(selected).shipSprite.destRect.x = boatX;

	//update animated sprite
	waterSprite.update();
	if(explosionActive)
		explosionSprite.update();

	if (splashActive)
		splashSprite.update();

	if (shellActive)
	{
		shellCoords.y+=2;
		shellSprite.destRect.y+=2;

		//Bullet hit its target
		if (shellCoords.y >= shellCoords.h) shellActive = false;

		//Bullet hit the ship
		//if (inHitBox(shellSprite.destRect.x, shellSprite.destRect.y, boats.at(selected).getHitbox(), Battleship::Game::gameScale))
		if(Hitbox::rectClickHit((shellSprite.destRect.x + 16), (shellSprite.destRect.y+16), boats.at(selected).getDest(), 1) && !shellActive)
		{
			explosionSprite.destRect.y = boats.at(selected).getDest().y;
			explosionSprite.destRect.x = shellCoords.x;
			explosionActive = true;
		}
		//Bullet hit the water
		else if (!shellActive)
		{
			splashSprite.destRect.y = shellCoords.y;
			splashSprite.destRect.x = shellCoords.x;
			splashActive = true;
		}
	}
	if (explosionActive)
	{
		explosionSprite.destRect.x -= 1;
		if (explosionSprite.currentIndex == explosionSprite.frameNum - 1)
		{
			explosionSprite.currentIndex = 0;
			explosionActive = false;
		}
	}
	if (splashActive)
	{
		if (splashSprite.currentIndex == splashSprite.frameNum - 1)
		{
			splashSprite.currentIndex = 0;
			splashActive = false;
		}
	}
}

void TitleScene::render()
{ 
	//Dark panels
	for (int x = 0; x < 20; x++)
	for (int y = 0; y < 16; y++)
	{
		metalPanelDark.destRect.x = x * 32;
		metalPanelDark.destRect.y = y * 32;
		TextureManager::Draw(metalPanelDark);
	}
	//Light panels
	for (int x = 6; x < 14; x++)
	for (int y = 2; y < 13; y++)
	{
		metalPanelLight.destRect.x = x * 32;
		metalPanelLight.destRect.y = y * 32;
		TextureManager::Draw(metalPanelLight);
	}
	//Water sprites
	for (int x = 0; x < 20; x++)
	for (int y = 13; y < 16; y++)
	{
		waterSprite.destRect.x = x * 32;
		waterSprite.destRect.y = y * 32;
		TextureManager::Draw(waterSprite);
	}

	//Any splashes rendered below boat
	if (splashActive)
		TextureManager::Draw(splashSprite);

	//Random boat
	boats.at(selected).render();

	//Mini game 
	if (shellActive)
		TextureManager::Draw(shellSprite);

	if (explosionActive)
		TextureManager::Draw(explosionSprite);

	//Button backgrounds
	for (SDL_Rect s : buttons)
	{
		buttonBG.destRect.x = s.x;
		buttonBG.destRect.y = s.y;
		TextureManager::Draw(buttonBG);
	}

	//Button text
	TextureManager::DrawText("PLAY", Colors::RED, PLAYbutton.x + 10, PLAYbutton.y + 5, 2);
	TextureManager::DrawText("EXIT", Colors::RED, EXITbutton.x + 20, EXITbutton.y + 5, 2);

	//Title text (Sprite)
	TextureManager::Draw(titleText);

	//Github info 
	TextureManager::DrawText("https://github.com/cjmar/battleship", Colors::BLACK, 14 * 32 + 1, 12 * 32 + 1, 0.45f);
}

void TitleScene::mouseDown(int, int, int) 
{ 
	//std::cout << "Scene::mouseDown() not overriden!\n"; 
}

void TitleScene::mouseUp(int x, int y, int button)
{ 
	int i = 0;
	for (SDL_Rect s : buttons)
	{
		//if (inHitBox(x, y, s, Battleship::Game::gameScale))
		if (Hitbox::rectClickHit(x, y, s, Battleship::Game::gameScale))
		{
			switch (i)
			{
			case 0: //VSAi
				playEvent();
				break;

			case 1: //EXIT
				Battleship::Game::quit();
				break;

			}
		}
		i++;
	}
	//Minigame if you click on the water
	if (Hitbox::rectClickHit(x, y, seaArea, Battleship::Game::gameScale) && !shellActive)
	{
		shellCoords.x = shellSprite.destRect.x = int(x / Battleship::Game::gameScale) - 16; 
		shellCoords.y = shellSprite.destRect.y = 13 * 32 - 8;

		shellCoords.w = x;
		shellCoords.h = int(y / Battleship::Game::gameScale) - 16;
		shellActive = true;
	}
}

void TitleScene::mouseMove(int, int)
{ 
	//std::cout << "Scene::mouseMove() not overriden!\n";
}

void TitleScene::playEvent()
{
	SceneManager::getInstance()->startScene(SceneManager::OnGoing);
}

