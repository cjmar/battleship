#include "SceneManager.h"
#include "GameScene.h"
#include "EndScene.h"
#include "TitleScene.h"
#include "Game.h"

using namespace Battleship;

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{ 
	instance = this;
	scale = Game::gameScale; 
	currentScene = nullptr;
	p2API = new OpponentAPI();
	gameWon = 0;
}

SceneManager::~SceneManager() 
{
	instance = nullptr;
	delete instance;
}

void SceneManager::startScene(SceneType t_in)
{
	sceneType = t_in;

	currentScene = nullptr;
	delete currentScene;

	switch (sceneType)
	{
		//Player has yet to choose how to play
	case TitleScreen:
		currentScene = new TitleScene();
		break;

		//Player has chosen to play against AI 
	case OnGoing:
		gameWon = 0;
		currentScene = new GameScene(true, p2API);
		break;

		//Game has ended
	case GameEnd:
		currentScene = new EndScene(gameWon);
		//Player may go to titlescreen or restart
		break;
	}
	currentScene->init();
}

void SceneManager::update()
{
	currentScene->update();
}

void SceneManager::render()
{
	currentScene->render();
}

void SceneManager::mouseDownEvent(int x, int y, int button)
{
	currentScene->mouseDown(x, y, button);
}

void SceneManager::mouseUpEvent(int x, int y, int button)
{
	currentScene->mouseUp(x, y, button);
}

void SceneManager::mouseMoveEvent(int x, int y)
{
	currentScene->mouseMove(int(x / Game::gameScale), int(y / Game::gameScale));
}


SceneManager* SceneManager::getInstance()
{
	return instance;
}

void SceneManager::setGameWon(int won_in)
{
	gameWon = won_in;
}