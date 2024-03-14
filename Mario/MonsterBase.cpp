#include "MonsterBase.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"
#include "PhysicsActor.h"
#include "BlockBase.h"
#include "MonsterScore.h"
#include "GreenTroopa.h"

MonsterBase::MonsterBase()
{
}

MonsterBase::~MonsterBase()
{
}

void MonsterBase::BeginPlay()
{
	DirState = EActorDir::Left;
}

void MonsterBase::Tick(float _DeltaTime)
{
	float CurLocationX = GetActorLocation().X;
	if (MarioHelper::CameraX + MarioHelper::WindowCenter < CurLocationX - 100.f && (MonsterState::CrouchMove != State))
	{
		return;
	}
	else if (!IsInit) {
		IsInit = true;
		MonsterInit();
	}
	StateUpdate(_DeltaTime);

	CollisionEvent(_DeltaTime);

	if (CurLocationX < MarioHelper::CameraX - 32) {
		Destroy();
	}

	if (State == MonsterState::CrouchMove && CurLocationX > MarioHelper::CameraX + MarioHelper::WindowCenter + 200) {
		Destroy();
	}
}

void MonsterBase::IsEdge(float _DeltaTime)
{
	FVector CurLocation = GetActorLocation();

	GreenTroopa* GTroopa = dynamic_cast<GreenTroopa*>(this);
	if (GTroopa != nullptr) {
		if (State == MonsterState::Idle) {
			bool LeftBottom = MarioHelper::LeftCheck({ CurLocation.X + 8, CurLocation.Y + 4 });
			bool RightBottom = MarioHelper::RightCheck({ CurLocation.X - 8, CurLocation.Y + 4 });

			Color8Bit PosColor = MarioHelper::ColMapImage->GetColor(CurLocation.iX(), CurLocation.iY(), Color8Bit(0, 0, 0, 0));
			bool PosColorCheck = (Color8Bit(255, 0, 255, 0) == PosColor);

			if (!LeftBottom && PosColorCheck) {
				ReverseDir();
				return;
			}

			if (!RightBottom && PosColorCheck) {
				ReverseDir();
				return;
			}
		}
	}


	bool IsLeft = MarioHelper::LeftCheck({ CurLocation.X + 4, CurLocation.Y - 10 });
	bool IsRight = MarioHelper::RightCheck({ CurLocation.X - 4, CurLocation.Y - 10 });
	if (IsLeft) {
		ReverseDir();
		return;
	}

	if (IsRight) {
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
	case MonsterState::Fly:
		Fly(_DeltaTime);
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
	case MonsterState::Fly:
		FlyStart();
		break;
	default:
		break;
	}
}

void MonsterBase::CollisionEvent(float _DeltaTime)
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
			if (Player->GetState() != MarioState::TelePortEnd && Player->GetState() != MarioState::TelePorting) {
				Player->Hit();
			}
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

	std::vector<UCollision*> BlockResult;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Block, BlockResult))
	{
		SpeedY.Y = 0;
		GravitySpeed.Y = 0;
		for (UCollision* Collision : BlockResult) {
			SetActorLocation({ GetActorLocation().X,Collision->GetActorBaseTransform().Top() });
			BlockBase* Block = (BlockBase*)Collision->GetOwner();
			if (Block->GetState() == BlockState::Interactive) {
				SetMonsterState(MonsterState::Excute);
			}
		}
	}

	ResultMove(_DeltaTime);
}

void MonsterBase::Crouch(float _DeltaTime)
{
	if (ChangeTime >= 0) {
		ChangeTime -= _DeltaTime;
	}

	if (ChangeTime <= 4.0f && ChangeTime >= 0) {
		SetAnimation("CrouchChange");
	}
	else if (ChangeTime <= 0) {
		SetMonsterState(MonsterState::Idle);
	}

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
	if (!ScoreSpawn) {
		ScoreSpawn = true;
		MarioHelper::AddMonsterScore(100);
		MonsterScore* Score = GetWorld()->SpawnActor<MonsterScore>(MarioRenderOrder::UI);
		Score->SetActorLocation(GetActorLocation());
	}
}

void MonsterBase::Excute(float _DeltaTime)
{
	if (!ScoreSpawn) {
		ScoreSpawn = true;
		MarioHelper::AddMonsterScore(100);
		MonsterScore* Score = GetWorld()->SpawnActor<MonsterScore>(MarioRenderOrder::UI);
		Score->SetActorLocation(GetActorLocation());
	}
	GravitySpeed += MarioHelper::Gravity * _DeltaTime;
	ResultMove(_DeltaTime);
	Destroy(3.f);
}

void MonsterBase::Fly(float _DeltaTime)
{
}

void MonsterBase::IdleStart()
{
	SetAnimation("Idle");
}

void MonsterBase::CrouchStart()
{
	ChangeTime = 8.0f;
	BGMPlayer = UEngineSound::SoundPlay("Stomp.wav");
	BodyCollision->SetScale({ 32,36 });
	SetAnimation("Crouch");
}

void MonsterBase::CrouchMoveStart()
{
	BGMPlayer = UEngineSound::SoundPlay("Stomp.wav");
	InteractiveDirCheck();
	SetAnimation("Crouch");
}

void MonsterBase::DeadStart()
{
	BGMPlayer = UEngineSound::SoundPlay("Stomp.wav");
	SetAnimation("Dead");
	Destroy(1.f);
}

void MonsterBase::ExcuteStart()
{
	BGMPlayer = UEngineSound::SoundPlay("Stomp.wav");
	SetAnimation("Excute");
	GravitySpeed.Y = 0.f;
	SpeedX.X = 0.f;
	SpeedY.Y = -500.f;
	BodyCollision->Destroy();
}

void MonsterBase::FlyStart()
{
	SetAnimation("Fly");
}

void MonsterBase::MonsterInit()
{
}
