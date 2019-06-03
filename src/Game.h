#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SceneManager.h"
#include "SDL2/SDL_ttf.h"

namespace Battleship
{
	namespace
	{
		SDL_Color RED = { 255, 0, 0 };
		SDL_Color MANGO = { 240, 50, 50 };
		SDL_Color BLACK = { 0, 0, 0 };
		SDL_Color WHITE = { 255, 255, 255 };
	}

	class Game
	{
	public:
		Game();
		~Game();
		void init(char*, int, int);
		bool isRunning();
		void update(unsigned int);

		static void quit();

		unsigned int getFrameNum();
		void eventHandler();
		void render();
		void clean();

		void changeScene(SceneManager::SceneType);

		static int GAME_WIDTH;
		static int GAME_HEIGHT;
		static TTF_Font* font;

		SceneManager sceneManager;
		static SDL_Renderer* renderer;
		static SDL_Texture* spriteSheet;
		static float gameScale;

		static bool spriteCollide(Sprite &, Sprite &);
		static bool rectCollide(SDL_Rect &, SDL_Rect &);
		static void printRect(SDL_Rect &);

		static int mouseX;
		static int mouseY;

	private:
		//SDL2 stuff
		SDL_Window* window;

		//Game specific
		static bool running;
		unsigned int frameNum;
	};
}
#endif