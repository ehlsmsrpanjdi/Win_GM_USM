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

	Collision = CreateCollision(MarioCollisionOrder::Monster);
	Collision->SetTransform({ { 0,-24 }, { 32, 48 } });
}

void Goomba::Tick(float _DeltaTime)
{
	AutoMove(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == Collision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		if (IsDead) {
			return;
		}
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
			DeadStart();
		}
		else {
			return;
		}


	}

}

void Goomba::DeadStart()
{
	IsDead = true;
	SetAnimation("Dead");
	Destroy(1.f);
}

void Goomba::Idle()
{
}

void Goomba::AutoMove(float _DeltaTime, FVector _SpeedX)
{
	if (IsDead) {
		return;
	}
	GravityCheck(_DeltaTime);
	FVector CurLocation = GetActorLocation();
	FVector XVector = (_SpeedX) * static_cast<float>(DirState) * _DeltaTime;
	FVector NextVector = XVector + CurLocation;
	SetActorLocation(NextVector);
}
