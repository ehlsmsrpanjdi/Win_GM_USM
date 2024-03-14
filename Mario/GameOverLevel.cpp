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
	MarioHelper::SoundOff = true;
	MarioHelper::SetPrevLevel("GameOver");
}

void GameOverLevel::LevelEnd(ULevel* _Level)
{
	MarioHelper::SetNextLevel("Stage1");
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
		GEngine->DestroyLevel("GameOver");
		MarioHelper::CreateLevel("Title");
		GEngine->ChangeLevel("Title");
	}
}
