#include "UpPipe.h"
#include "MarioHelper.h"
#include "Mario.h"
#include <EnginePlatform/EngineInput.h>


UpPipe::UpPipe()
{
}

UpPipe::~UpPipe()
{
}

void UpPipe::BeginPlay()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Object);
	BodyCollision->SetTransform({ { 0,0 } ,{32,128} });

	BodyRenderer = CreateImageRenderer(MarioRenderOrder::Cheat);
	BodyRenderer->SetTransform({ {0,0}, {128, 128} });
	BodyRenderer->SetImage("UpPipe.png");
}

void UpPipe::Tick(float _DeltaTime)
{
	//if (TotalMove < -128.f) {
	//	return;
	//}
	//std::vector<UCollision*> Result;
	//if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	//{
	//	NotCollision = false;
	//	Mario* Player;
	//	UCollision* Collision = Result[0];
	//	Player = (Mario*)Collision->GetOwner();

	//	Player->SetState(MarioState::TelePorting);

	//	Player->AddActorLocation(FVector::Up * 100 * _DeltaTime);
	//	TotalMove += FVector::Up.Y * 100 * _DeltaTime;
	//}

}

