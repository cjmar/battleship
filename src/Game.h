#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SceneManager.h"
#include "SDL2/SDL_ttf.h"

namespace Battleship
{
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