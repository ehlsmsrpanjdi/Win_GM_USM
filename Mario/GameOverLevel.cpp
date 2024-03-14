#include "GameOverLevel.h"
#include "MarioHelper.h"
#include "GameOverLogo.h"


GameOverLevel::GameOverLevel() 
{
}

GameOverLevel::~GameOverLevel() 
{
}

void GameOverLevel::BeginPlay()
{

	SpawnActor<GameOverLogo>();
}

void GameOverLevel::LevelStart(ULevel* _Level)
{
	
}

void GameOverLevel::LevelEnd(ULevel* _Level)
{
	MarioHelper::SetPrevLevel("Stage1");
	MarioHelper::SetNextLevel("Stage1");
	MarioHelper::CreateLevel("Stage1");
}

void GameOverLevel::Tick(float _DeltaTime)
{
	if (RestartTime >= 0) {
		RestartTime -= _DeltaTime;
	}
	else {
		RestartTime = 5.0f;
		MarioHelper::MarioLife = 3;
		MarioHelper::MarioTotalScore = 1000000;
		GEngine->ChangeLevel("Title");
	}
}
