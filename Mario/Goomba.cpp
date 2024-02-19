#include "Goomba.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"
#include "PhysicsActor.h"

Goomba::Goomba()
{
	DirState = EActorDir::Left;
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
	Renderer->SetTransform({ {0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 0, 1,0.2f);
	SetAnimation("Idle");

	AnimationAuto(Renderer, "Dead", 2, 2);

	BodyCollision= CreateCollision(MarioCollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,-24 }, { 64, 64} });

	State = MonsterState::Idle;
}

void Goomba::Tick(float _DeltaTime)
{

	StateUpdate(_DeltaTime);

	CollisionEvent(State);

}

void Goomba::IsEdge(float _DeltaTime)
{
	EActorDir Dir = DirState;

	Color8Bit Color_Right = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX() + 5, GetActorLocation().iY() - 20, Color8Bit::MagentaA);
	Color8Bit Color_Left = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX() - 5, GetActorLocation().iY() - 20, Color8Bit::MagentaA);

	if (Color_Right == Color8Bit(255, 0, 255, 0))
	{
		ReverseDir();
		return;
	}

	if (Color_Left == Color8Bit(255, 0, 255, 0))
	{
		ReverseDir();
		return;
	}

}

void Goomba::ReverseDir()
{
	if (DirState == EActorDir::Left) {
		DirState = EActorDir::Right;
	}

	else if (DirState == EActorDir::Right) {
		DirState = EActorDir::Left;
	}

	SetAnimation(CurAnimationName);
}

void Goomba::DeadStart()
{
	SetAnimation("Dead");
	Destroy(1.f);
}

void Goomba::Idle(float _DeltaTime)
{
	IsEdge(_DeltaTime);
	SpeedX.X = MonsterDefaultSpeed * static_cast<int>(DirState);
	GravityCheck(_DeltaTime);
	ResultMove(_DeltaTime);
}

void Goomba::IdleStart()
{
}

void Goomba::StateUpdate(float _DeltaTime)
{
	
	switch (State)
	{
	case MonsterState::None:
		break;
	case MonsterState::Idle:
		Idle(_DeltaTime);
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

	else if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Monster, Result))
	{
		for (UCollision* Collision : Result) {
			if (Collision != this->BodyCollision) {
				this->ReverseDir();
			}
			else {
				int a = 0;
			}
		}
	}

}
