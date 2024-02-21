#include "Plant.h"

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
}

void Plant::Tick(float _DeltaTime)
{
	Update(_DeltaTime);

	CollisionEvent(State);

}

void Plant::Update(float _DeltaTime)
{
	if (StartLocation.X == 0 && StartLocation.Y == 0) {
		StartLocation = GetActorLocation();
		NextLocation = StartLocation + FVector{ 0.f, -64.f };
	}

	FVector CurLocation = GetActorLocation();

	if (CurLocation.Y > NextLocation.Y && IsUp) {
		AddActorLocation({ 0.f, SpawnTime * _DeltaTime });
	}

	else if (IsUp) {
		if (TotalMove >= 0.f) {
			TotalMove -= _DeltaTime;
		}
		else {
			IsUp = false;
			TotalMove = 2.f;
			SetActorLocation(NextLocation);
		}
	}

	else if (CurLocation.Y <= StartLocation.Y && !IsUp) {
		AddActorLocation({ 0.f, -SpawnTime * _DeltaTime });
	}
	else {
		if (TotalMove >= 0.f) {
			TotalMove -= _DeltaTime;
		}
		else {
			IsUp = true;
			TotalMove = 2.f;
			SetActorLocation(StartLocation);
		}
	}
}

