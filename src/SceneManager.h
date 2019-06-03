#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include <vector>
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "OpponentAPI.h"

class SceneManager
{
public:
	enum SceneType
	{
		TitleScreen,
		OnGoing,
		GameEnd,

		size,
	};

	SceneManager();
	~SceneManager();

	float scale;

	void update();
	void render();
	void startScene(SceneType);
	void mouseDownEvent(int, int, int);
	void mouseUpEvent(int, int, int);
	void mouseMoveEvent(int, int);
	void setGameWon(int);

	static SceneManager* getInstance();

private:
	int gameWon;
	Scene* currentScene;
	static SceneManager* instance;
	OpponentAPI* p2API;
	SceneType sceneType;
};

#endif