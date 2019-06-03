#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "Scene.h"
#include "Sprite.h"

class EndScene : public Scene
{
public:
	EndScene(int);
	~EndScene();

	void update();
	void render();
	void mouseDown(int, int, int);
	void mouseUp(int, int, int);
	void mouseMove(int, int);
	void init();

private:
	void drawUIBox(int, int, int, int);

	const char* message;
	int gameWon;
	float textScale;

	int WIDTH;
	int HEIGHT;

	SDL_Rect exitBox;
	SDL_Rect playBox;

	Sprite waterSprite;
	Sprite redButton;

	Sprite LT;
	Sprite LM;
	Sprite LB;

	Sprite MT;
	Sprite MM;
	Sprite MB;

	Sprite RT;
	Sprite RM;
	Sprite RB;
};

#endif