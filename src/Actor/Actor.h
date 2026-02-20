#pragma once
#include <iostream>
#include "SDL2/include/SDL.h"
#include "Components/SpriteComponent/SpriteComponent.h"

class Actor
{
public:

  Actor();
  virtual ~Actor();

   SpriteComponent* SpriteComp;

   void GetActorRect();

   void SetActorRectSizeLoc(int x, int y, int w, int h);

   void SetSurface(std::string Address);

   void SetTexture(SDL_Renderer* MyRen);

   void RenderActor(SDL_Renderer* MyRen);

};

