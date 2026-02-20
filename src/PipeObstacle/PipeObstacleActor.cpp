#include "PipeObstacleActor.h"

int RandomRange(int min, int max)
{
	return min + rand() % (max - min + 1);
}

PipeObstacleActor::PipeObstacleActor()
{
	SpriteUpperPipe = new SpriteComponent();
	SpriteLowerPipe = new SpriteComponent();

	bHasScored = false;
}

PipeObstacleActor::~PipeObstacleActor()
{
	delete SpriteUpperPipe;
	SpriteUpperPipe = nullptr;
	
	delete SpriteLowerPipe;
	SpriteLowerPipe = nullptr;
}

void PipeObstacleActor::GetActorRectUpperPipe()
{
	if (SpriteUpperPipe)
	{
		SpriteUpperPipe->MyPlayerRect;
	}
}

void PipeObstacleActor::GetActorRectLowerPipe()
{
	if (SpriteLowerPipe)
	{
		SpriteLowerPipe->MyPlayerRect;
	}
}

void PipeObstacleActor::SetActorRectUpperPipeSizeLoc(int x, int y, int w, int h)
{
	if (SpriteUpperPipe)
	{
		SpriteUpperPipe->SetPlayerSizeLoc(x, y, w, h);
	}
}

void PipeObstacleActor::SetActorRectLowerPipeSizeLoc(int x, int y, int w, int h)
{
	if (SpriteLowerPipe)
	{
		SpriteLowerPipe->SetPlayerSizeLoc(x, y, w, h);
	}
}

void PipeObstacleActor::SetSurfaceUpperPipe(std::string Address)
{
	if (SpriteUpperPipe)
	{
		SpriteUpperPipe->SetSurface(Address);
	}
}

void PipeObstacleActor::SetSurfaceLowerPipe(std::string Address)
{
	if(SpriteLowerPipe)
	{
		SpriteLowerPipe->SetSurface(Address);
	}
}


void PipeObstacleActor::SetTexture(SDL_Renderer* MyRen)
{
	if (SpriteUpperPipe)
	{
		SpriteUpperPipe->SetTexture(MyRen);
	}
	if (SpriteLowerPipe)
	{
		SpriteLowerPipe->SetTexture(MyRen);
	}
}

void PipeObstacleActor::RenderActor(SDL_Renderer* MyRen)
{
	if (SpriteUpperPipe)
	{
		SpriteUpperPipe->RenderActor(MyRen);
	}
	if (SpriteLowerPipe)
	{
		SpriteLowerPipe->RenderActor(MyRen);
	}
}

void PipeObstacleActor::Update(float deltatime , float Speed, int WindowWidth)
{
	//speed += Speed * deltatime;
	//	MyPipeObstacleActor->SetActorRectUpperPipeSizeLoc(400, 0, 52, 400);
	//  MyPipeObstacleActor->SetActorRectLowerPipeSizeLoc(400, 555, 52, 400); //x 0 to 300 and y 0 to 600

	// 	MyPipeObstacleActor->SetActorRectUpperPipeSizeLoc(400, -100, 52, 400);
	//  MyPipeObstacleActor->SetActorRectLowerPipeSizeLoc(400, 400, 52, 400);



	//if (SpriteUpperPipe)
	//{
		//float NewLoc = SpriteUpperPipe->GetSpriteRectX() - (deltatime * Speed);
		//SpriteUpperPipe->SetSpriteRectX(NewLoc);

		//float Width = SpriteUpperPipe->MyPlayerRect.w;

		//if (NewLoc + Width < 0)
		//{
			//SpriteUpperPipe->SetSpriteRectX(WindowWidth);
		//}
	//}
	//if (SpriteLowerPipe)
	//{
		//float NewLoc = SpriteLowerPipe->GetSpriteRectX() - (deltatime * Speed);
		//SpriteLowerPipe->SetSpriteRectX(NewLoc);

		//float Width = SpriteLowerPipe->MyPlayerRect.w;

		//if (NewLoc + Width < 0)
		//{
			//SpriteLowerPipe->SetSpriteRectX(WindowWidth);
		//}

	//}

	if (!SpriteUpperPipe || !SpriteLowerPipe)
		return;

	
	float NewLoc = SpriteUpperPipe->GetSpriteRectX() - (deltatime * Speed);

	SpriteUpperPipe->SetSpriteRectX(NewLoc);
	SpriteLowerPipe->SetSpriteRectX(NewLoc);

	float Width = SpriteUpperPipe->MyPlayerRect.w;

	GapScoreRect.x = NewLoc + (Width / 2);

	if (NewLoc + Width < 0)
	{
		int GapSize = 130;
		int PipeHeight = 500;
		int WindowHeight = 600; 

		int LowerPipeY = RandomRange(300, 600);

		int UpperPipeY = LowerPipeY - GapSize - PipeHeight;

		SpriteUpperPipe->SetSpriteRectX(WindowWidth);
		SpriteLowerPipe->SetSpriteRectX(WindowWidth);

		SpriteUpperPipe->SetSpriteRectY(UpperPipeY);
		SpriteLowerPipe->SetSpriteRectY(LowerPipeY);

		GapScoreRect.x = WindowWidth + (Width / 2);
		GapScoreRect.y = UpperPipeY + PipeHeight;
		GapScoreRect.w = 5;
		GapScoreRect.h = GapSize;

		//Reset
		bHasScored = false;
    }
}
