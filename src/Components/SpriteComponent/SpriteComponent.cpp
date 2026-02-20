#include "SpriteComponent.h"

SpriteComponent::SpriteComponent():myTexture(nullptr),mySurface(nullptr)
{
	std::cout << "SpriteComponent Constructor called" << std::endl;
}

SpriteComponent::~SpriteComponent()
{
	std::cout << "SpriteComponent Destructor called" << std::endl;

	SDL_DestroyTexture(myTexture);
	myTexture = nullptr;
}

void SpriteComponent::SetPlayerSizeLoc(int x, int y, int w, int h)
{
	MyPlayerRect.x = x;
	MyPlayerRect.y = y;
	MyPlayerRect.w = w;
	MyPlayerRect.h = h;
}

void SpriteComponent::SetSpriteRectY(int y)
{
	MyPlayerRect.y = y;
}

int SpriteComponent::GetSpriteRectY()
{
	return MyPlayerRect.y;
}

void SpriteComponent::SetSpriteRectX(int x)
{
	MyPlayerRect.x = x;
}

int SpriteComponent::GetSpriteRectX()
{
	return MyPlayerRect.x;
}

int SpriteComponent::GetSpriteWidth()
{
	return MyPlayerRect.w;
}

int SpriteComponent::GetSpriteHeight()
{
	return MyPlayerRect.h;
}

void SpriteComponent::SetSurface(std::string Address)
{
	mySurface = SDL_LoadBMP(Address.c_str());
}

void SpriteComponent::SetTexture(SDL_Renderer* MyRen)
{
	if (mySurface != nullptr)
	{
		myTexture = SDL_CreateTextureFromSurface(MyRen, mySurface);

		if (myTexture != nullptr)
		{
			SDL_FreeSurface(mySurface);
			mySurface = nullptr;
		}
	}
}

void SpriteComponent::RenderActor(SDL_Renderer* MyRen)
{
	if (MyRen != nullptr)
	{
		SDL_RenderCopy(MyRen, myTexture, NULL, &MyPlayerRect);
	}
}

