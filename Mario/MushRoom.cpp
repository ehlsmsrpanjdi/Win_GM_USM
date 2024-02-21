#include "MushRoom.h"
#include "Mario.h"

MushRoom::MushRoom()
{
}

MushRoom::~MushRoom()
{
}

void MushRoom::BeginPlay()
{
	DirState = EActorDir::Right;
	SetName("Item");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Item);
	Renderer->SetImage("Item.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });


	AnimationAuto(Renderer, "Idle", 0, 0, 0.1f, false);

	SetAnimation("Idle");

	BodyCollision = CreateCollision(MarioCollisionOrder::Item);
	BodyCollision->SetTransform({ { 0, -32 }, { 64, 64} });
}

void MushRoom::Tick(float _DeltaTime)
{
	Spawn(_DeltaTime);
	ItemCollisionEvent();
}

void MushRoom::Spawn(float _DeltaTime)
{
	if (TotalMove >= -64.f) {
		AddActorLocation({ 0.f,SpawnTime * _DeltaTime });
		TotalMove += SpawnTime * _DeltaTime;
	}
	else {
		IsEdge(_DeltaTime);
		SpeedX.X = ItemDefaultSpeed * static_cast<int>(DirState);
		GravityCheck(_DeltaTime);
		ResultMove(_DeltaTime);
	}
}

void MushRoom::ItemCollisionEvent()
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		Destroy();
	}


}

