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
	Renderer->SetTransform({ {0,0 }, { 256,256 } });
	AnimationAuto(Renderer, "Idle", 0, 1, false, 0.3f);
	SetAnimation("Idle");
	SetState(MonsterState::Idle);
}

void Plant::Tick(float _DeltaTime)
{

	StateUpdate(_DeltaTime);

	//CollisionEvent(State);

}

void Plant::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case MonsterState::None:
		break;
	case MonsterState::Idle:
		AutoMove(_DeltaTime, {0.f,100.f});
		break;
	case MonsterState::Dead:
		break;
	default:
		break;
	}
}

void Plant::CollisionEvent(MonsterState _State)
{
}

void Plant::AutoMove(float _DeltaTime, FVector _SpeedX)
{
	FVector CurLocation = GetActorLocation();
	FVector CurVector = (_SpeedX) * static_cast<float>(DirState) * _DeltaTime;
	FVector NextVector = CurVector + CurLocation;

	Time -= _DeltaTime;

	if (Time <= 0.f) {
		if (DirState == EActorDir::Left) {
			DirState = EActorDir::Right;

		}
		else if (DirState == EActorDir::Right) {
			DirState = EActorDir::Left;
		}
		Time = 1.f;
	}
	
	
	SetActorLocation(NextVector);
}

