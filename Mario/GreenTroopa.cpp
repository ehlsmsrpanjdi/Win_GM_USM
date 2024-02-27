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
		case MonsterState::Dead:
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
			case MonsterState::None:
				break;
			case MonsterState::Idle:
				this->ReverseDir();
				break;
			case MonsterState::Crouch:
				break;
			case MonsterState::Dead:
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

void GreenTroopa::MonsterInit()
{
	BodyCollision = CreateCollision(MarioRenderOrder::Monster);
	BodyCollision->SetTransform({ {0,-24},{32,48} });

	State = MonsterState::Idle;
}
