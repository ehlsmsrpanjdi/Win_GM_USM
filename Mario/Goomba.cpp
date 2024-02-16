#include "Goomba.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"

Goomba::Goomba()
{
}

Goomba::~Goomba()
{
}

void Goomba::BeginPlay()
{
	SetName("Goomba");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("Goomba.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });
	AnimationAuto(Renderer, "Idle", 0, 1, false, 0.2f);
	SetAnimation("Idle");

	AnimationAuto(Renderer, "Dead", 2, 2, false, 1.f);

	BodyCollision= CreateCollision(MarioCollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,-24 }, { 32, 48 } });
	DirState = EActorDir::Right;

	State = MonsterState::Idle;
}

void Goomba::Tick(float _DeltaTime)
{

	StateUpdate(_DeltaTime);

	CollisionEvent(State);

}

void Goomba::DeadStart()
{
	SetAnimation("Dead");
	Destroy(1.f);
}

void Goomba::Idle()
{
}

void Goomba::IdleStart()
{
}

void Goomba::AutoMove(float _DeltaTime, FVector _SpeedX)
{
	GravityCheck(_DeltaTime);
	IsEdge(_DeltaTime);
	FVector CurLocation = GetActorLocation();
	FVector XVector = (_SpeedX) * static_cast<float>(DirState) * _DeltaTime;
	FVector NextVector = XVector + CurLocation;
	SetActorLocation(NextVector);
}

void Goomba::InteractiveDirCheck()
{
	if (Mario::PlayerLocation.X < GetActorLocation().X) {
		DirState = EActorDir::Right;
	}
	else {
		DirState = EActorDir::Left;
	}
}

void Goomba::StateUpdate(float _DeltaTime)
{
	
	switch (State)
	{
	case MonsterState::None:
		break;
	case MonsterState::Idle:
		AutoMove(_DeltaTime);
		break;
	case MonsterState::Dead:
		break;
	default:
		break;
	}
}

void Goomba::SetState(MonsterState _State)
{
	if (State != _State) {
		State = _State;
	}

	switch (State)
	{
	case MonsterState::None:
		break;
	case MonsterState::Idle:
		break;
	case MonsterState::Dead:
		DeadStart();
		break;
	default:
		break;
	}

}

void Goomba::CollisionEvent(MonsterState _MonsterState)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Mario* Player = dynamic_cast<Mario*>(Ptr);
		FVector CurPlayerLocation = Player->GetActorLocation();

		if (nullptr == Player)
		{
			MsgBoxAssert("터져야겠지....");
		}
		FVector CurLocation = GetActorLocation();
		if (CurPlayerLocation.Y < CurLocation.Y - 32) {
			Player->SetState(MarioState::Interactive);
			BodyCollision->Destroy();
			SetState(MonsterState::Dead);
			return;
		}
		else {
			Player->Destroy();
			return;
		}
	}

}
