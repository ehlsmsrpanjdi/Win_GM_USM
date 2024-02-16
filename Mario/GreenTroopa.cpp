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
	Renderer->SetTransform({ {0,0 }, { 256,256} });
	AnimationAuto(Renderer, "Idle", 0, 1, true, 0.2f);
	SetAnimation("Idle");
	AnimationAuto(Renderer, "Crouch", 4, 4, true);

	BodyCollision = CreateCollision(MarioRenderOrder::Monster);
	BodyCollision->SetTransform({ {0,-24},{32,48} });

	State = MonsterState::Idle;

}

void GreenTroopa::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	CollisionEvent(State);


}

void GreenTroopa::IsEdge(float _DeltaTime)
{
	Color8Bit Color = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);

	if (Color != Color8Bit(255, 0, 255, 0))
	{
		if (EActorDir::Left == DirState) {
			DirState = EActorDir::Right;
		}
		else {
			DirState = EActorDir::Left;
		}
	}
}

void GreenTroopa::CrouchStart()
{
	SetAnimation("Crouch");
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

		FVector CurLocation = GetActorLocation();
		if (CurPlayerLocation.Y < CurLocation.Y - 32) {
			Player->SetState(MarioState::Interactive);
			switch (_MonsterState)
			{
			case MonsterState::None:
				break;
			case MonsterState::Idle:
				SetState(MonsterState::Crouch);
				break;
			case MonsterState::Crouch:
				SetState(MonsterState::CrouchMove);
				break;
			case MonsterState::CrouchMove:
				SetState(MonsterState::Crouch);
				break;
			case MonsterState::Dead:
				break;
			default:
				break;
			}
			return;
		}
		else {
			Player->Destroy();
			return;
		}
	}

}

void GreenTroopa::CrouchMoveStart()
{
}

void GreenTroopa::CrouchMove(float _DeltaTime)
{
	AutoMove(_DeltaTime, { 400.f,0.f });
}

void GreenTroopa::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case MonsterState::None:
		break;
	case MonsterState::Idle:
		AutoMove(_DeltaTime);
		break;
	case MonsterState::Crouch:

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
