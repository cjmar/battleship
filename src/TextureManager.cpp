#include "TextureManager.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include "Game.h"

using namespace Battleship;

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	SDL_Surface *temp = IMG_Load(fileName);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, temp);
	SDL_FreeSurface(temp);

	if (!texture)
	{
		std::cout << "Failed to load texture " << fileName << "\n";
	}

	return texture;
}

void TextureManager::Draw(Sprite &s)
{
	TextureManager::Draw(s.srcRect.at(s.currentIndex), s.destRect);
}

void TextureManager::Draw(SDL_Rect &src, SDL_Rect &dest)
{
	SDL_Rect scaledDest = {int(dest.x * Game::gameScale), int(dest.y * Game::gameScale), int(dest.w * Game::gameScale), int(dest.h * Game::gameScale) };
	SDL_RenderCopy(Game::renderer, Game::spriteSheet, &src, &scaledDest);
}


void TextureManager::DrawText(const char* text, SDL_Color& color, int xPos, int yPos, float scale)
{
	SDL_Surface* tSurface = TTF_RenderText_Solid(Game::font, text, color);
	SDL_Texture* tTexture = SDL_CreateTextureFromSurface(Game::renderer, tSurface);

	SDL_Rect dest = { xPos * Game::gameScale, yPos * Game::gameScale, tSurface->w * scale, tSurface->h * scale };
	SDL_RenderCopy(Game::renderer, tTexture, NULL, &dest);

	SDL_FreeSurface(tSurface);
	SDL_DestroyTexture(tTexture);
}

void TextureManager::getSpriteSrc(SpriteName name, Sprite &s)
{
	//return sprites.at(name);
	SDL_Rect Rect;
	SDL_Rect hitbox; //x y offset based on destRect, then w, h based on non transparent values in sprite
	switch (name)
	{
	case Carrier:
		Rect = { 0, 0, 32, 160 };
		hitbox = {0, 2, 0, -5};
		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case rCarrier:
		Rect = { 160, 0, 160, 32 };
		hitbox = { 2, 0, -5, 0 };
		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case Battleship:
		Rect = { 32, 0, 32, 128 };
		hitbox = { 7, 1, -15, -2 };

		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case rBattleship:
		Rect = { 192, 32, 128, 32 };
		hitbox = { 1, 7, -2, -15 }; 

		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case Cruiser:
		Rect = { 64, 0, 32, 96 };
		hitbox = { 7, 1, -14, -2 };

		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case rCruiser:
		Rect = { 224, 64, 96, 32 };
		hitbox = { 1, 7, -2, -14 };

		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case Submarine:
		Rect = { 96, 0, 32, 96 };
		hitbox = { 10, 1, -20, -7 };

		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;
			
	case rSubmarine:
		Rect = { 224, 96, 96, 32 };
		hitbox = { 1, 10, -7, -20 };

		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case Destroyer:
		Rect = { 128, 0, 32, 64 };
		hitbox = { 9, 0, -18, 0 };

		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case rDestroyer:
		Rect = { 256, 128, 64, 32 };
		hitbox = { 0, 9, 0, -18 };

		s.setSprite(Rect, hitbox, 1, 1, 0);
		break;

	case Water:
		Rect = { 0, 160, 160, 64 };
		s.setSprite(Rect, 5, 2, 400);
		break;

	case Explosion:
		Rect = {0, 224, 160, 64};
		s.setSprite(Rect, 5, 2, 100);
		break;

	case Splash:
		Rect = { 160, 192, 160, 32 };
		s.setSprite(Rect, 5, 1, 100);
		break;

	case Smoke:
		Rect = { 160, 160, 160, 32 };
		s.setSprite(Rect, 5, 1, 400);
		break;
	
	case Shell:
		Rect = { 64, 288, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case MetalPanelDark:
		Rect = {0, 288, 32, 32};
		s.setSprite(Rect, 1, 1, 0);
		break;

	case MetalPanelLight:
		Rect = { 32, 288, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case TitleText:
		Rect = {0, 320, 160, 32};
		s.setSprite(Rect, 1, 1, 0);
		break;

	case BlackX:
		Rect = { 128, 64, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case RedO:
		Rect = { 128, 96, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case Paper:
		Rect = { 64, 96, 64, 64 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case ButtonBGRed:
		Rect = { 96, 288, 64, 32 };
		s.setSprite(Rect, 1, 1, 0);
		s.destRect.w = int(s.destRect.w * 1.5);
		s.destRect.h = int(s.destRect.h * 1.5);
		break;

	case ButtonBGBlack:
		Rect = { 160, 320, 64, 32 };
		s.setSprite(Rect, 1, 1, 0);
		s.destRect.w = int(s.destRect.w * 2);
		s.destRect.h = int(s.destRect.h * 2);
		break;

	case x3TLEFT:
		Rect = { 160, 224, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case x3LEFT:
		Rect = { 160, 256, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case x3BLEFT:
		Rect = { 160, 288, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case x3TMID:
		Rect = { 192, 224, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case x3MID:
		Rect = { 192, 256, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case x3BMID:
		Rect = { 192, 288, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case x3TRIGHT:
		Rect = { 224, 224, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case x3RIGHT:
		Rect = { 224, 256, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case x3BRIGHT:
		Rect = { 224, 288, 32, 32 };
		s.setSprite(Rect, 1, 1, 0);
		break;

	case Flag:
		Rect = { 128, 128, 128, 32 };
		s.setSprite(Rect, 4, 1, 200);
		break;
	}
}
