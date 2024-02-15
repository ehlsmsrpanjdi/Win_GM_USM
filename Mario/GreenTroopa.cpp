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

	Collision = CreateCollision(MarioRenderOrder::Monster);
	Collision->SetTransform({ {0,-24},{32,48} });
}

void GreenTroopa::Tick(float _DeltaTime)
{
	if (!IsCrouch) {
		AutoMove(_DeltaTime);
	}
	

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

		if (IsCrouch) {
			AutoMove(_DeltaTime, { 200.f, 0.f });
		}

		if (CurPlayerLocation.Y < CurLocation.Y - 32) {
			Player->SetState(MarioState::Interactive);
			SetCrouch();
		}
		else {
			return;
		}


	}


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

void GreenTroopa::SetCrouch()
{
	SetAnimation("Crouch");
	IsCrouch = true;
}

