#pragma once
#include "Actor/Actor.h"

class PipeObstacleActor;

class Player : public Actor
{
public:
	 Player();
	~Player();

	bool bIsJumping;

	float VerticalVelocity;
	float Gravity;
	float JumpStrength;

	SDL_Rect& GetPlayerRect()
	{
		return SpriteComp->MyPlayerRect;
	}

	void SetPlayerGravity(float deltatime, int velocity);
	void SetPlayerJump(float deltatime, int velocity);

	void UpdatePlayer(float deltatime);

	bool isOutBoundWindow(int WindHeight);

	bool bIsCollideWithPipeObstacle(PipeObstacleActor* MyPipObstacleActor);
	bool bIsCollideWithScore(PipeObstacleActor* MyPipObstacleActor);
};

