#include "ContentsCore.h"
#include "TitleLevel.h"
#include "TitleLogo.h"
#include "MarioHelper.h"
#include "MarioUI.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	SpawnActor<TitleLogo>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	if (UEngineInput::IsAnykeyDown()) {
		GEngine->ChangeLevel("Loading");
	}
}

void UTitleLevel::LevelStart(ULevel* _Level)
{
	MarioHelper::SoundOff = true;
	MarioHelper::SetPrevLevel("Title");
	MarioHelper::SetNextLevel("Stage1");
}

