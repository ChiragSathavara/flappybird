#include "Game.h"
#include "CustomActor/Background/Background.h"
#include "CustomActor/Player/Player.h"
#include "PipeObstacle/PipeObstacleActor.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Game::Game()
{
	bIsRunning = false;
	bIsGameStart = false;
	bIsGameOver = false;
	PBirdAState = OneFlap;
	ScoreText = 0;
	srand(static_cast<unsigned int>(time(nullptr)));
}

Game::~Game()
{
	DestroyGame();
}

void Game::BGImplementation()
{
	MyBGActor = new Background();
	MyBGActor->SetActorRectSizeLoc(0, 0, 400, 800);
	MyBGActor->SetSurface("./sprites/background-day.bmp");
	MyBGActor->SetTexture(MyRen);
}

void Game::PlayerImplementation()
{
	PlayerActor = new Player();
	PlayerActor->SetActorRectSizeLoc(100, 100, 34, 24);
	PlayerActor->SetSurface("./sprites/redbird-downflap.bmp");
	PlayerActor->SetTexture(MyRen);
}

void Game::PipeObstacleImplementation()
{
	MyPipeObstacleActor = new PipeObstacleActor();
	MyPipeObstacleActor->SetActorRectUpperPipeSizeLoc(400, -300, 52, 500);
	MyPipeObstacleActor->SetActorRectLowerPipeSizeLoc(400, 400, 52, 500); //x 0 to 300 and y 0 to 600
	MyPipeObstacleActor->SetSurfaceUpperPipe("./sprites/pipegreendown23.bmp");
	MyPipeObstacleActor->SetSurfaceLowerPipe("./sprites/pipegreendown.bmp");
	MyPipeObstacleActor->SetTexture(MyRen);
}

void Game::GameOverTitleImplementation()
{
	GameOverTitleActor = new Actor();
	GameOverTitleActor->SetActorRectSizeLoc(100, 300, 200, 60);
	GameOverTitleActor->SetSurface("./sprites/gameover.bmp");
	GameOverTitleActor->SetTexture(MyRen);
}

void Game::GameStartTitleImplementation()
{
	GameStartTitleActor = new Actor();
	GameStartTitleActor->SetActorRectSizeLoc(50, 150, 300, 400);
	GameStartTitleActor->SetSurface("./sprites/message.bmp");
	GameStartTitleActor->SetTexture(MyRen);
}

void Game::GameTextTitleImplementation()
{
	GameScoreActor = new Actor();
	GameScoreActor->SetActorRectSizeLoc(190, 10, 30, 30);
	GameScoreActor->SetSurface("./sprites/0.bmp");
	GameScoreActor->SetTexture(MyRen);
}

void Game::InitGame()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_INIT_EVERYTHING_FAILED" << std::endl;
		return;
	}

	//SDL_DisplayMode myDisplaymode;
	//SDL_GetCurrentDisplayMode(0, &myDisplaymode);

	WindHeight = 800; //myDisplaymode.h;
	WindWidth = 400;//myDisplaymode.w;

	MyWind = SDL_CreateWindow("G1_GAME_ENGINE",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WindWidth,WindHeight,SDL_WINDOW_BORDERLESS);

	if (MyWind == nullptr)
	{
		return;
	}

	MyRen = SDL_CreateRenderer(MyWind, 0, 0);

	if (MyRen == nullptr)
	{
		return;
	}
 
	BGImplementation();

	PipeObstacleImplementation();

	GameOverTitleImplementation();

	GameStartTitleImplementation();

	GameTextTitleImplementation();

	bIsRunning = true;
}

void Game::ProcessInput()
{
	SDL_Event myEvent;
	while (SDL_PollEvent(&myEvent))
	{
		switch (myEvent.type)
		{
		    case SDL_QUIT:
				bIsRunning = false;
			break;

			case SDL_KEYDOWN:

				if(myEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					bIsRunning = false;
				}
				if (myEvent.key.keysym.sym == SDLK_SPACE)
				{
					if(bIsGameStart == false)
					{
						std::cout << "Press W to start the game!!" << std::endl;
						return;
					}
					PlayerActor->VerticalVelocity = -PlayerActor->JumpStrength;
					std::cout << "BIRD JUMPING!!" << std::endl;
				}
				if(myEvent.key.keysym.sym == SDLK_w)
				{
					if(bIsGameStart == false)
					{
						PlayerImplementation();
						bIsGameStart = true;
					}
					else
					{
						std::cout << "Game is already started!!" << std::endl;
					}
				
				}
				if (myEvent.key.keysym.sym == SDLK_d)
				{
					std::cout << "D Pressed" << std::endl;
				}
			break;

			default:
				
			break;
		}

		/*const Uint8* keystate = SDL_GetKeyboardState(nullptr);

		if(keystate[SDL_SCANCODE_SPACE])
		{
			PlayerActor->bIsJumping = true;
		}
		 else
		{
			PlayerActor->bIsJumping = false;
		}*/
	}
}

void Game::Update()
{
	Uint32 TimeToDelay = MIL_SEC_PER_FRAME - (SDL_GetTicks() - MIL_SEC_PREVIOUS_FRAME);
	if(TimeToDelay > 0 && TimeToDelay <= MIL_SEC_PER_FRAME)
	{
		SDL_Delay(TimeToDelay);
	}
	
	ElapsedTime = SDL_GetTicks();
	DeltaTime = (ElapsedTime - MIL_SEC_PREVIOUS_FRAME) / 1000.0f;
	MIL_SEC_PREVIOUS_FRAME = SDL_GetTicks();

	if(PlayerActor == nullptr)
	{
		return;
	}
	
	if (MyPipeObstacleActor == nullptr)
	{
		return;
	}
	
	if(bIsGameStart == false)
	{
		return;
	}

	if(bIsGameOver == true)
	{
		return;
	}

	PlayerActor->UpdatePlayer(DeltaTime);
	MyPipeObstacleActor->Update(DeltaTime, 180, 400);
	
	if(PlayerActor->isOutBoundWindow(WindHeight))
	{
		std::cout << "GameOver!!" << std::endl;
		bIsGameOver = true;
	}

	if(PlayerActor->bIsCollideWithPipeObstacle(MyPipeObstacleActor))
	{
		std::cout << "Bird Collide With Pipe GameOver!!" << std::endl;
		bIsGameOver = true;
	}

	if (!MyPipeObstacleActor->bHasScored &&SDL_HasIntersection(&PlayerActor->GetPlayerRect(),&MyPipeObstacleActor->GapScoreRect))
	{
		++ScoreText;
		MyPipeObstacleActor->bHasScored = true;
		std::cout << "Bird Collide With ScoreBox = " << ScoreText << std::endl;
	}

	AnimationSpeed += DeltaTime;

	if (AnimationSpeed >= frameTimer)
	{
		AnimationSpeed = 0.0f;

		switch (PBirdAState)
		{
		case OneFlap:
			PlayerActor->SetSurface("./sprites/redbird-downflap.bmp");
			PlayerActor->SetTexture(MyRen);
			PBirdAState = TwoFlap;
			break;

		case TwoFlap:
			PlayerActor->SetSurface("./sprites/redbird-midflap.bmp");
			PlayerActor->SetTexture(MyRen);
			PBirdAState = ThreeFlap;
			break;

		case ThreeFlap:
			PlayerActor->SetSurface("./sprites/redbird-upflap.bmp");
			PlayerActor->SetTexture(MyRen);
			PBirdAState = OneFlap;
			break;
		}
	}
}

void Game::RunGame()
{
	while (bIsRunning == true)
	{
		ProcessInput();
		Update();
		RenderGame();
	}
}

void Game::RenderGame()
{
	SDL_SetRenderDrawColor(MyRen, 21, 21, 21, 255);
	SDL_RenderClear(MyRen);
	
	if (MyBGActor)
	{
		MyBGActor->RenderActor(MyRen);
	}
	if(MyPipeObstacleActor)
	{
		MyPipeObstacleActor->RenderActor(MyRen);
	}
	if (PlayerActor)
	{
		PlayerActor->RenderActor(MyRen);
	}

	if (bIsGameStart == false)
	{
		GameStartTitleActor->RenderActor(MyRen);
	}

	if (bIsGameOver == true)
	{
		GameOverTitleActor->RenderActor(MyRen);
	}

	if (GameScoreActor)
	{
		GameScoreActor->RenderActor(MyRen);
	}


	SDL_RenderPresent(MyRen);
}

void Game::DestroyGame()
{
	SDL_DestroyWindow(MyWind);
	SDL_DestroyRenderer(MyRen);

	delete MyBGActor;
	delete MyPipeObstacleActor;
	delete PlayerActor;
	delete GameOverTitleActor;
	delete GameStartTitleActor;
	delete GameScoreActor;

	MyBGActor = nullptr;
	MyPipeObstacleActor = nullptr;
	PlayerActor = nullptr;
	GameOverTitleActor = nullptr;
	GameStartTitleActor = nullptr;
	GameScoreActor = nullptr;

	SDL_Quit();
}
