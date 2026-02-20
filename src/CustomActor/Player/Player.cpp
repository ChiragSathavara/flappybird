#include "Player.h"
#include "PipeObstacle/PipeObstacleActor.h"

Player::Player()
{
	VerticalVelocity = 0.0f;
	Gravity = 980.0f;       // pixels per second squared
	JumpStrength = 400.0f;  // jump force
}

Player::~Player()
{

}

void Player::SetPlayerGravity(float deltatime, int velocity)
{
	if (SpriteComp && bIsJumping == false)
	{
		float NewLoc = SpriteComp->GetSpriteRectY() + (deltatime * velocity);
		SpriteComp->SetSpriteRectY(NewLoc);
	}
}

void Player::SetPlayerJump(float deltatime, int velocity)
{
	if (SpriteComp)
	{
		bIsJumping = true;
		SpriteComp->SetSpriteRectY(SpriteComp->GetSpriteRectY() - (deltatime * velocity));
	}
}

void Player::UpdatePlayer(float deltatime)
{
	VerticalVelocity += Gravity * deltatime;
	
	float NewY = SpriteComp->GetSpriteRectY() + (VerticalVelocity * deltatime);
	SpriteComp->SetSpriteRectY(NewY);
}

bool Player::isOutBoundWindow(int WindHeight)
{
	return SpriteComp->GetSpriteRectY() > WindHeight;
}

bool Player::bIsCollideWithPipeObstacle(PipeObstacleActor* MyPipObstacleActor)
{
	if(SDL_HasIntersection(&SpriteComp->MyPlayerRect, &MyPipObstacleActor->SpriteLowerPipe->MyPlayerRect) || SDL_HasIntersection(&SpriteComp->MyPlayerRect, &MyPipObstacleActor->SpriteUpperPipe->MyPlayerRect))
	{
		return true;
	}
}

bool Player::bIsCollideWithScore(PipeObstacleActor* MyPipObstacleActor)
{
if (SDL_HasIntersection(&SpriteComp->MyPlayerRect, &MyPipObstacleActor->GapScoreRect))
	{
		return true;
	}
}


