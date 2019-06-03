#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include <queue>
#include "Ship.h"
#include "Player.h"
#include "OpponentAPI.h"
#include <vector>

class GameScene : public Scene
{
public:

	//the lock button
	enum SceneState
	{
		SettingUp,
		OnGoing,
		PlayAnim,
		GameEnd,
	};

	GameScene(bool, OpponentAPI *);
	~GameScene();
	void init();

	void update();
	void render();
	void mouseDown(int, int, int);
	void mouseUp(int, int, int);
	void mouseMove(int, int);

private:
	//UI Sprites
	Sprite metalPanel;
	Sprite titleText;
	Sprite lockButton;

	Sprite LT;
	Sprite LM;
	Sprite LB;

	Sprite MT;
	Sprite MM;
	Sprite MB;

	Sprite RT;
	Sprite RM;
	Sprite RB;

	//Ship dragging
	void shipClickEvent(int, int, int);
	void markClickEvent(int, int, int);
	bool shipOnMouse;
	bool markOnMouse;
	bool shipsLocked;
	bool marksLocked;
	
	int selected;
	SDL_Rect seaArea;

	//User interface
	void drawUIBox(int, int, int, int);
	void drawUI();
	void drawWater();
	void drawPaper();
	void drawMarks();
	bool lockSelectedToGrid(int, int);
	void lockButtonEvent();
	void devButtonEvent();
	void createFiveNewMarks();

	//Gameplay elements
	Sprite waterSprite;
	Sprite paperSprite;
	Sprite shellSprite;
	Sprite blackMark;
	Sprite redMark;
	Sprite flagSprite;
	bool vsAI;
	int gameWon;

	int delayTime;
	int delayCurrent;
	int roundNum;
	Player p1;
	OpponentAPI* p2;
	std::string p2Message;
	SceneState currentState;
	std::vector<SDL_Rect> newMarks;

	std::vector<SDL_Rect> p2Marks;
	std::vector<SDL_Rect> successOffHits;
	std::vector<SDL_Rect> successDefHits;
	std::vector<SDL_Rect> failedDefHits;
	std::vector<Sprite> explosions;
	std::vector<Sprite> splashes;
	std::vector<Sprite> smoke;

	void firingPhase();
	void markingPhase();
	void setupPhase();
};

#endif