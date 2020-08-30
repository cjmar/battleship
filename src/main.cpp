/* 
	Battleship game using SDL2
	
	A grid:
		"Ocean" area of game where ships are placed

	A cell:
		a 32x32 area

	Ships:
		Carrier		32 x 160 (5 cells)
		Battleship	32 x 128 (4 cells)
		Cruiser		32 x 96	 (3 cells)
		Submarine	32 x 96  (3 cells)
		Destroyer	32 x 64	 (2 cells)

	Gameplay:
			Each player starts by setting up the location of their ships on the board
			The location of the opponents ships is a secret
			
			When it is the players turn, they will describe cells which to attack
			The number of guesses (salvo) each player gets is based on how many ships they have
			5 ships = 5 shot salvo, 4 ships = 4 shot salvo, etc...

			If a player correctly guesses the location of one of the opponents ships
				then that ship will be hit, and that cell will be marked as a hit for the player
*/
#if _DEBUG
	#define SDL_MAIN_HANDLED
#endif

#include <Windows.h>
#include "SDL2/SDL.h"
#include "Game.h"
#include <string>

/*
	15 cell x 15 cell board
	32 * 1.5 = 48 (scaled textures by 1.5)
	48 * 15 = 720 x 720 pixels for play area
	5 cells for UI = 5 * 48 = 240 + 720 = 960 width
		
*/

#if _DEBUG
	int main(int argc, char** argv)
#else
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
#endif
{
	Battleship::Game game;
	char title[] = "Battleship";
	const int WINDOW_WIDTH = 960; 
	const int WINDOW_HEIGHT = 768;

	game.init(title, WINDOW_WIDTH, WINDOW_HEIGHT);

	//Framerate 
	int fps = 60;
	int frameDelay = 1000 / fps;
	Uint32 frameStart;
	int frameTime;
	unsigned int frameNum = 0;

	while(game.isRunning())
	{
		//Start of frame
		frameStart = SDL_GetTicks();
		frameNum++;

		game.eventHandler();
		game.update(frameNum);
		game.render();

		//End of frame
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game.clean();

	return 0;
}
