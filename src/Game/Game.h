#pragma once

#include "SDL2/include/SDL.h"
#include "SDL2/include/SDL_ttf.h"

const int FPS = 60;
const int MIL_SEC_PER_FRAME = 1000 / FPS;

class Background;
class Player;
class PipeObstacleActor;
class Actor;

enum PlayerBirdAnimationState 
{
	OneFlap,
	TwoFlap,
	ThreeFlap
};


class Game
{
public:
	Game();
   ~Game();

   void BGImplementation();
   void PlayerImplementation();
   void PipeObstacleImplementation();
   void GameOverTitleImplementation();
   void GameStartTitleImplementation();
   void GameTextTitleImplementation();
   void GameScoreTextImplementation(int Score);
   
   void InitGame();
   void ProcessInput();
   void Update();
   void RunGame();
   void RenderGame();
   void DestroyGame();

private:

	int WindHeight;
	int WindWidth;

	int ScoreText;
	TTF_Font* ScoreFont = nullptr;
	SDL_Surface* ScoreSurface = nullptr;
	SDL_Texture* ScoreTexture = nullptr;

	Uint32 MIL_SEC_PREVIOUS_FRAME;
	float DeltaTime;
	float ElapsedTime;

	float AnimationSpeed;
	float frameTimer = 0.1f;

	bool bIsRunning;
	bool bIsGameStart;
	bool bIsGameOver;

	SDL_Window* MyWind;
	SDL_Renderer* MyRen;

	SDL_Rect MyScoreTextRect;

	PlayerBirdAnimationState PBirdAState;

	

	//Background
	Background* MyBGActor;

	//Player
	Player* PlayerActor;


	//PipeObstacle
	PipeObstacleActor* MyPipeObstacleActor;

	//GameOverTitle
	Actor* GameOverTitleActor;

	//GameStartTitle
	Actor* GameStartTitleActor;

	Actor* GameScoreActor;
};

