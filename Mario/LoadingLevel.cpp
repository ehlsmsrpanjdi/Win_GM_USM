#include "LoadingLevel.h"
#include "MarioUI.h"
#include "MarioHelper.h"
#include "CollisionActor.h"
#include "LoadingUI.h"
#include "Mario.h"

LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}

void LoadingLevel::BeginPlay()
{
	float a = GEngine->MainWindow.GetWindowScale().hX();
	float  b = GEngine->MainWindow.GetWindowScale().hY();

	SetName("Loading");
	MarioUI* UI = SpawnActor<MarioUI>(MarioRenderOrder::UI);
	UI->SetActorLocation({ 200,200 });

	BackGroundMap* Map;
	Map = SpawnActor<BackGroundMap>(MarioRenderOrder::Map);
	Map->SetCollisionActorImage(GetName(), true);
	Map->Renderer->SetTransform({ { a, b }, {1024, 960} });

	LoadingUI* LoadingLevelUI;
	LoadingLevelUI = SpawnActor<LoadingUI>(MarioRenderOrder::UI);
	LoadingLevelUI->SetActorLocation({ 200,200 });
}

void LoadingLevel::Tick(float _DeltaTime)
{

	if (LevelChangeTime <= 0) {
		std::string LevelName = MarioHelper::GetPrevLevel();
		std::string NextName = MarioHelper::GetNextLevel();
		LevelChangeTime = 3.f;

		if (MarioHelper::MarioLife <= 0) {
			GEngine->ChangeLevel("GameOver");

			return;
		}

		if (LevelName._Equal(NextName)) {
			MarioHelper::CreateLevel(LevelName);
			GEngine->ChangeLevel(LevelName);
		}

		else {
			MarioHelper::CreateLevel(NextName);
			GEngine->ChangeLevel(NextName);
		}

	}
	else {
		LevelChangeTime -= _DeltaTime;
	}
}

void LoadingLevel::LevelStart(ULevel* Level)
{
	Mario::PlayerLocation = { 0,0 };
	MarioHelper::CameraX = 0;
	MarioHelper::MarioWorldSet();
	MarioHelper::CameraOff = false;
	MarioHelper::SoundOff = false;
	GEngine->DestroyLevel(MarioHelper::GetPrevLevel());
}

void LoadingLevel::LevelEnd(ULevel* Level)
{
	MarioHelper::MarioTimeReset();
}



