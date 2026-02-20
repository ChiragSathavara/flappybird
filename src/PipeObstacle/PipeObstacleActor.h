#pragma once
#include "Components/SpriteComponent/SpriteComponent.h"

class PipeObstacleActor
{
public:
	PipeObstacleActor();
	~PipeObstacleActor();

	SpriteComponent* SpriteUpperPipe;
	SpriteComponent* SpriteLowerPipe;
	
	SDL_Rect GapScoreRect;
	bool bHasScored;
	void GetActorRectUpperPipe();
	void GetActorRectLowerPipe();

	void SetActorRectUpperPipeSizeLoc(int x, int y, int w, int h);
	void SetActorRectLowerPipeSizeLoc(int x, int y, int w, int h);

	void SetSurfaceUpperPipe(std::string Address);

	void SetSurfaceLowerPipe(std::string Address);

	void SetTexture(SDL_Renderer* MyRen);

	void RenderActor(SDL_Renderer* MyRen);

	void Update(float deltatime, float Speed, int WindowWidth);

private:

	float speed;

};

