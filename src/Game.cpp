#include "Game.h"
#include <iostream>
#include "TextureManager.h"

bool DRAW_GRID = false;

using namespace Battleship;

SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* Game::spriteSheet = nullptr;
bool Game::running = false;
TTF_Font* Game::font = nullptr;

int Game::GAME_WIDTH = 0;
int Game::GAME_HEIGHT = 0;
int Game::mouseX = 0;
int Game::mouseY = 0;

float Game::gameScale = 1.5;

Game::Game() { window = nullptr; }

Game::~Game() {}

void Game::init(char* title, int width, int height)
{
	Game::GAME_WIDTH = width;
	Game::GAME_HEIGHT = height;

	//initialize SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::GAME_WIDTH, Game::GAME_HEIGHT, 0);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		if (!IMG_Init(IMG_INIT_PNG))
		{
			std::cout << IMG_GetError() << "\n";
		}
		if (TTF_Init() == 0)
		{
			font = TTF_OpenFont("assets/Peace.ttf", 30);
			if (font == nullptr)
			{
				std::cout << "TTF_OpenFont() says: \"" << TTF_GetError() << "\" \n";
			}
		}
		running = true;
	}

	spriteSheet = TextureManager::loadTexture("assets/atlas.png");

	sceneManager.startScene(SceneManager::TitleScreen);
}

//Called every frame
void Game::update(unsigned int frame)
{
	frameNum = frame;
	sceneManager.update();
}

void Game::eventHandler()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//System events
		switch (event.type)
		{
		case SDL_QUIT:
			quit();
			break;

		//Keyboard events
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
			case SDLK_UP:
				
				break;
			}

		//Mouse motion event
		case SDL_MOUSEMOTION:
			Game::mouseX = event.motion.x;
			Game::mouseY = event.motion.y;

			sceneManager.mouseMoveEvent(Game::mouseX, Game::mouseY);
			break;

		case SDL_MOUSEBUTTONDOWN:
			sceneManager.mouseDownEvent(Game::mouseX, Game::mouseY, event.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			sceneManager.mouseUpEvent(Game::mouseX, Game::mouseY, event.button.button);
			break;
		}

	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	sceneManager.render();

	if (DRAW_GRID)
	{
		//Draw a grid to help debugging
		SDL_SetRenderDrawColor(Battleship::Game::renderer, 0, 0, 0, 255);
		for (int x = 0; x < Battleship::Game::GAME_WIDTH; x += 48)
		{
			SDL_RenderDrawLine(Battleship::Game::renderer, x, 0, x, Battleship::Game::GAME_HEIGHT);
		}
		for (int y = 0; y < Battleship::Game::GAME_HEIGHT; y += 48)
		{
			SDL_RenderDrawLine(Battleship::Game::renderer, 0, y, Battleship::Game::GAME_WIDTH, y);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
}

bool Game::isRunning() { return running; };

void Game::quit() { running = false; };

unsigned int Game::getFrameNum() { return frameNum; };

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::changeScene(SceneManager::SceneType type_in)
{
	sceneManager.startScene(type_in);
}

//Dest rect collision
bool Game::spriteCollide(Sprite &s1, Sprite &s2)
{
	return rectCollide(s1.destRect, s2.destRect);
}

//Dest rect collision
bool Game::rectCollide(SDL_Rect& r1, SDL_Rect& r2)
{
	bool collide = false;

	if (r1.x < r2.x + r2.w &&
		r1.x + r1.w > r2.x &&
		r1.y < r2.y + r2.h &&
		r1.y + r1.h > r2.y)

		collide = true;

	return collide;
}

void Game::printRect(SDL_Rect& r)
{
	std::cout << "{" << r.x << ", " << r.y << ", " << r.w << ", " << r.h << "}\n";
}