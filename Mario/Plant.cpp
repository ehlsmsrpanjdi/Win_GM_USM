#include "Plant.h"
#include "Mario.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"

Plant::Plant()
{
}

Plant::~Plant()
{
}

void Plant::BeginPlay()
{
	SetName("Plant");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("Plant.png");
	Renderer->SetTransform({ {0,0 }, { 512,512 } });


	AnimationAuto(Renderer, "Idle", 0, 1, 0.2f, true);

	SetAnimation("Idle");

	BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0, -32 }, { 64, 64} });
	CheatCollision = CreateCollision(MarioCollisionOrder::Object);
	CheatCollision->SetTransform({ {0,0},{160,640} });
}

void Plant::StateUpdate(float _DeltaTime)
{
	if (StartLocation.X == 0 && StartLocation.Y == 0) {
		StartLocation = GetActorLocation();
		NextLocation = StartLocation + FVector{ 0.f, +64.f };
	}

	FVector CurLocation = GetActorLocation();

	switch (PlantState)
	{
	case 1:
		AddActorLocation(FVector::Down * _DeltaTime * SpawnTime);
		if (CurLocation.Y > NextLocation.Y) {
			PlantState++;
		}
		break;
	case 2:
	{
		TotalMove += _DeltaTime;
		std::vector<UCollision*> Result;
		if (CheatCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
			return;
		}
		if (TotalMove >= 2.0f) {
			PlantState++;
			TotalMove = 0.f;
		}
	}
	break;
	case 3:
		AddActorLocation(FVector::Up * _DeltaTime * SpawnTime);
		if (CurLocation.Y < StartLocation.Y) {
			PlantState++;
		}
		break;
	case 4:
		TotalMove += _DeltaTime;
		if (TotalMove >= 2.0f) {
			PlantState = 1;
			TotalMove = 0.f;
		}
		break;
	default:
		break;
	}

}

void Plant::CollisionEvent(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Mario* Player = dynamic_cast<Mario*>(Ptr);
		Player->Hit();
	}

	std::vector<UCollision*> MResult;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Fire, MResult))
	{
		MResult[0]->GetOwner()->Destroy();
		Destroy();
	}
}

