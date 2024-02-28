#include "LoadingLevel.h"
#include "MarioUI.h"
#include "MarioHelper.h"
#include "CollisionActor.h"
#include "LoadingUI.h"

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
	if (UEngineInput::IsDown('U')) {
		GEngine->ChangeLevel("Stage1");
	}
}

void LoadingLevel::LevelEnd(ULevel* Level)
{
	MarioHelper::MarioTimeReset();
	MarioHelper::MarioCoinReset();
}



