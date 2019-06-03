#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "Scene.h"
#include "Sprite.h"
#include <vector>
#include "SceneManager.h"
#include "Ship.h"

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();
	void init();

	void update();
	void render();
	void mouseDown(int, int, int);
	void mouseUp(int, int, int);
	void mouseMove(int, int);

private:
	SDL_Rect PLAYbutton;
	SDL_Rect EXITbutton;

	//Mini game 
	SDL_Rect seaArea;
	bool shellActive;
	bool explosionActive;
	bool splashActive;
	SDL_Rect shellCoords;


	Sprite buttonBG;
	Sprite titleText;

	Sprite metalPanelDark;
	Sprite metalPanelLight;
	Sprite waterSprite;
	Sprite explosionSprite;
	Sprite shellSprite;
	Sprite splashSprite;

	std::vector<Ship> boats;
	int selected;
	int boatX;
	int boatY;

	void playEvent();

	std::vector<SDL_Rect> buttons;
};

#endif