#include "GreenTroopa.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"
#include "MonsterBase.h"

GreenTroopa::GreenTroopa()
{
}

GreenTroopa::~GreenTroopa()
{
}

void GreenTroopa::FlyInit(FVector _StartPos, FVector _EndPos)
{
	StartPos = _StartPos;
	EndPos = _EndPos;
}

void GreenTroopa::BeginPlay()
{
	MonsterBase::BeginPlay();
	SetName("GreenTroopa");
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("GreenTroopa_Right.png");
	Renderer->SetTransform({ {0,0 }, { 512,512} });
	AnimationAuto(Renderer, "Idle", 0, 1, 0.2f);
	SetAnimation("Idle");
	AnimationAuto(Renderer, "Crouch", 4, 4);
	AnimationAuto(Renderer, "Fly", 2, 3, 0.2f);
	SetMonsterState(MonsterState::Idle);
}

void GreenTroopa::CollisionEvent(float _DeltaTime)
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
				SetMonsterState(MonsterState::Crouch);
				return;
			}
			else {
				Player->Hit();
				return;
			}
		}
		break;
		case MonsterState::Crouch:
			SetMonsterState(MonsterState::CrouchMove);
			break;
		case MonsterState::CrouchMove:
		{
			FVector CurLocation = GetActorLocation();
			if (CurPlayerLocation.Y < CurLocation.Y - 32) {
				Player->SetState(MarioState::Interactive);
				SetMonsterState(MonsterState::Crouch);
				return;
			}
			else {
				Player->Hit();
				return;
			}
			break;
		}
		case MonsterState::Fly:
		{
			FVector CurLocation = GetActorLocation();
			if (CurPlayerLocation.Y < CurLocation.Y - 32) {
				Player->SetState(MarioState::Interactive);
				SetMonsterState(MonsterState::Idle);
				return;
			}
			else {
				Player->Hit();
				return;
			}
		}
		break;
		default:
			break;
		}
	}

	std::vector<UCollision*> MonsterResult;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Monster, MonsterResult))
	{
		for (UCollision* Collision : MonsterResult) {
			switch (State)
			{
			case MonsterState::Idle:
				this->ReverseDir();
				break;
			case MonsterState::CrouchMove:
			{
				MonsterBase* Test = (MonsterBase*)(Collision->GetOwner());
				Test->SetMonsterState(MonsterState::Excute);
			}
			break;
			default:
				break;
			}

		}
	}

}

void GreenTroopa::Fly(float _DeltaTime)
{
	FVector DirPos = (EndPos - StartPos);
	FVector DirPosNormal = DirPos.Normalize2DReturn();
	FVector CurAcc = DirPosNormal * _DeltaTime * Speed;
	if (abs(CurSpeed.X + CurAcc.X) <= MaxSpeed && abs(CurSpeed.Y + CurAcc.Y) <= MaxSpeed) {
		CurSpeed += CurAcc;
	}
	AddActorLocation(CurSpeed * _DeltaTime);
	FVector CurLocation = GetActorLocation();
	float SubX = EndPos.X - CurLocation.X;
	float SubY = EndPos.Y - CurLocation.Y;
	if (abs(SubX) + abs(SubY) < 10) {
		FVector TempLocation = StartPos;
		StartPos = EndPos;
		EndPos = TempLocation;
	}
}

void GreenTroopa::MonsterInit()
{
	BodyCollision = CreateCollision(MarioRenderOrder::Monster);
	BodyCollision->SetTransform({ {0,-24},{32,48} });
}
