#pragma once
#include <iostream>
#include "SDL2/include/SDL.h"
class SpriteComponent
{
public:

	SpriteComponent();
	~SpriteComponent();

	void SetPlayerSizeLoc(int x, int y, int w, int h);
	
	void SetSpriteRectY(int y);
	int GetSpriteRectY();

	void SetSpriteRectX(int x);
	int GetSpriteRectX();

	int GetSpriteWidth();
	int GetSpriteHeight();

	void SetSurface(std::string Address);
	void SetTexture(SDL_Renderer* MyRen);

	void RenderActor(SDL_Renderer* MyRen);

	SDL_Rect  MyPlayerRect;

private:
	SDL_Texture* myTexture;
	SDL_Surface* mySurface;

};

