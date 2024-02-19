#include "GreenTroopa.h"

#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"

GreenTroopa::GreenTroopa()
{
}

GreenTroopa::~GreenTroopa()
{
}

void GreenTroopa::BeginPlay()
{
	SetName("GreenTroopa");
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("GreenTroopa_Right.png");
	Renderer->SetTransform({ {0,0 }, { 512,512} });
	AnimationAuto(Renderer, "Idle", 0, 1, 0.2f);
	SetAnimation("Idle");
	AnimationAuto(Renderer, "Crouch", 4, 4);

	BodyCollision = CreateCollision(MarioRenderOrder::Monster);
	BodyCollision->SetTransform({ {0,-24},{32,48} });

	State = MonsterState::Idle;

}

void GreenTroopa::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	CollisionEvent(State);
}


void GreenTroopa::Crouch(float _DeltaTime)
{
}

void GreenTroopa::CrouchStart()
{
	BodyCollision->SetScale({ 32,36 });
	SetAnimation("Crouch");
}

void GreenTroopa::CrouchMove(float _DeltaTime)
{
	IsEdge(_DeltaTime);
	SpeedX.X = CrouchDefaultMoveSpeed * static_cast<int>(DirState);
	GravityCheck(_DeltaTime);
	ResultMove(_DeltaTime);
}


void GreenTroopa::SetState(MonsterState _State)
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
	case MonsterState::Crouch:
		CrouchStart();
		break;
	case MonsterState::CrouchMove:
		CrouchMoveStart();
		break;
	case MonsterState::Dead:
		DeadStart();
		break;
	default:
		break;
	}

}

void GreenTroopa::CollisionEvent(MonsterState _MonsterState)
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

		switch (State)
		{
		case MonsterState::None:
			break;
		case MonsterState::Idle:
		{
			FVector CurLocation = GetActorLocation();
			if (CurPlayerLocation.Y < CurLocation.Y - 32) {
				Player->SetState(MarioState::Interactive);
				SetState(MonsterState::Crouch);
				return;
			}
			else {
				Player->Destroy();
				return;
			}
		}
		break;
		case MonsterState::Crouch:
			SetState(MonsterState::CrouchMove);
			break;
		case MonsterState::CrouchMove:
		{
			FVector CurLocation = GetActorLocation();
			if (CurPlayerLocation.Y < CurLocation.Y - 32) {
				Player->SetState(MarioState::Interactive);
				SetState(MonsterState::Crouch);
				return;
			}
			else {
				Player->Destroy();
				return;
			}
			break;
		}
		case MonsterState::Dead:
			break;
		default:
			break;
		}
	}
}
void GreenTroopa::CrouchMoveStart()
{
	InteractiveDirCheck();
}


void GreenTroopa::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case MonsterState::None:
		break;
	case MonsterState::Idle:
		Idle(_DeltaTime);
		break;
	case MonsterState::Crouch:
		Crouch(_DeltaTime);
		break;
	case MonsterState::CrouchMove:
		CrouchMove(_DeltaTime);
		break;
	case MonsterState::Dead:
		break;
	default:
		break;
	}

}

