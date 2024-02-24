#include "MonsterBase.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"
#include "PhysicsActor.h"

MonsterBase::MonsterBase() 
{
}

MonsterBase::~MonsterBase() 
{
}

void MonsterBase::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	CollisionEvent();
}

void MonsterBase::IsEdge(float _DeltaTime)
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

void MonsterBase::ReverseDir()
{
	if (DirState == EActorDir::Left) {
		DirState = EActorDir::Right;
	}

	else if (DirState == EActorDir::Right) {
		DirState = EActorDir::Left;
	}

	SetAnimation(CurAnimationName);
}

void MonsterBase::StateUpdate(float _DeltaTime)
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
		Dead(_DeltaTime);
		break;
	case MonsterState::Excute:
		Excute(_DeltaTime);
		break;
	default:
		break;
	}
}

void MonsterBase::SetMonsterState(MonsterState _State)
{
	if (State != _State) {
		State = _State;
	}

	switch (State)
	{
	case MonsterState::None:
		break;
	case MonsterState::Idle:
		IdleStart();
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
	case MonsterState::Excute:
		ExcuteStart();
		break;
	default:
		break;
	}
}

void MonsterBase::CollisionEvent()
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Mario* Player = dynamic_cast<Mario*>(Ptr);
		FVector CurPlayerLocation = Player->GetActorLocation();

		FVector CurLocation = GetActorLocation();
		if (CurPlayerLocation.Y < CurLocation.Y - 32) {
			Player->SetState(MarioState::Interactive);
			BodyCollision->Destroy();
			SetMonsterState(MonsterState::Dead);
			return;
		}
		else {
			Player->Hit();
			return;
		}
	}

	std::vector<UCollision*> MonsterResult;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Monster, MonsterResult))
	{
		for (UCollision* Collision : MonsterResult) {
			this->ReverseDir();
		}
	}


}

void MonsterBase::InteractiveDirCheck()
{
	{
		if (Mario::PlayerLocation.X < GetActorLocation().X) {
			DirState = EActorDir::Right;
		}
		else {
			DirState = EActorDir::Left;
		}
	}
}

void MonsterBase::Idle(float _DeltaTime)
{
	IsEdge(_DeltaTime);
	SpeedX.X = MonsterDefaultSpeed * static_cast<int>(DirState);
	GravityCheck(_DeltaTime);
	ResultMove(_DeltaTime);
}

void MonsterBase::Crouch(float _DeltaTime)
{
}

void MonsterBase::CrouchMove(float _DeltaTime)
{
	IsEdge(_DeltaTime);
	SpeedX.X = CrouchDefaultMoveSpeed * static_cast<int>(DirState);
	GravityCheck(_DeltaTime);
	ResultMove(_DeltaTime);
}

void MonsterBase::Dead(float _DeltaTime)
{
	ScoreRendererLocation += {0.f, -0.1f};
	ScoreRenderer->SetTransform({ ScoreRendererLocation, {60,20} });
}

void MonsterBase::Excute(float _DeltaTime)
{
	GravitySpeed += MarioHelper::Gravity * _DeltaTime;
	ResultMove(_DeltaTime);
	Destroy(3.f);
}

void MonsterBase::IdleStart()
{
}

void MonsterBase::CrouchStart()
{
	BodyCollision->SetScale({ 32,36 });
	SetAnimation("Crouch");
}

void MonsterBase::CrouchMoveStart()
{
	InteractiveDirCheck();
}

void MonsterBase::DeadStart()
{
	SetAnimation("Dead");
	Destroy(1.f);
	ScoreRenderer = CreateImageRenderer(MarioRenderOrder::UI);
	FVector OwnerLocation = this->GetActorLocation();
	ScoreRenderer->SetImage("100.png");
	ScoreRenderer->SetTransform({ {0,-20}, {60,20} });
	ScoreRendererLocation = ScoreRenderer->GetTransform().GetPosition();
	MarioHelper::MarioTotalScore += 100;
}

void MonsterBase::ExcuteStart()
{
	GravitySpeed.Y = 0.f;
	SpeedX.X = 0.f;
	SpeedY.Y = -500.f;
	BodyCollision->Destroy();
}
