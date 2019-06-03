#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL2/SDL.h"
#include <vector>
#include "Sprite.h"
#include "SDL2/SDL_ttf.h"

class TextureManager
{
public:
	enum SpriteName
	{
		//Boats
		Carrier,
		rCarrier,
		Battleship,
		rBattleship,
		Cruiser,
		rCruiser,
		Submarine,
		rSubmarine,
		Destroyer,
		rDestroyer,

		//Animated Sprites
		Water,
		Explosion,
		Smoke,
		Splash,

		//user interface
		MetalPanelDark,
		MetalPanelLight,
		TitleText,
		BlackX,
		RedO,
		Paper,
		ButtonBGRed,
		ButtonBGBlack,
		Flag,
		
		//3x3 UI panel
		x3TLEFT,
		x3LEFT,
		x3BLEFT,
		x3TMID,
		x3MID,
		x3BMID,
		x3TRIGHT,
		x3RIGHT,
		x3BRIGHT,

		//Other
		Shell,

		Size,
	};

	static void Draw(SDL_Rect &, SDL_Rect &);
	static void Draw(Sprite &);
	static void DrawText(const char*, SDL_Color &, int, int, float);
	static void getSpriteSrc(SpriteName, Sprite &);
	static SDL_Texture* loadTexture(const char*);

};

#endif