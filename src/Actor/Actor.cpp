#include "Actor.h"


Actor::Actor()
{
	std::cout << "Actor Constructor called" << std::endl;
	
	SpriteComp = new SpriteComponent();
}

Actor::~Actor()
{
	delete SpriteComp;
	SpriteComp = nullptr;

	std::cout << "Actor Destructor called" << std::endl;
}

void Actor::GetActorRect()
{
	if (SpriteComp)
	{
		SpriteComp->MyPlayerRect;
	}
}

void Actor::SetActorRectSizeLoc(int x, int y, int w, int h)
{
	if (SpriteComp)
	{
		SpriteComp->SetPlayerSizeLoc(x, y, w, h);
	}
}

void Actor::SetSurface(std::string Address)
{
	if (SpriteComp)
	{
		SpriteComp->SetSurface(Address);
	}
}

void Actor::SetTexture(SDL_Renderer* MyRen)
{
	if (SpriteComp)
	{
		SpriteComp->SetTexture(MyRen);
	}
}

void Actor::RenderActor(SDL_Renderer* MyRen)
{
	if (SpriteComp)
	{
		SpriteComp->RenderActor(MyRen);
	}
}
