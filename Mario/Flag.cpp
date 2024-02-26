#include "Flag.h"
#include "Mario.h"

Flag::Flag()
{
}

Flag::~Flag()
{
}

void Flag::BeginPlay()
{
	SetName("Flag");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("Flag.png");
	Renderer->SetTransform({ {0,0 }, { 64,688 } });




	BodyCollision = CreateCollision(MarioCollisionOrder::Block);
	BodyCollision->SetTransform({ { 0, 0 }, { 16, 688} });

	BottomCollision = CreateCollision(MarioCollisionOrder::Block);
	BottomCollision->SetTransform({ { 0,312 }, { 64,64 } });
}

void Flag::Tick(float _DeltaTime)
{
	CollisionEvent();
}

void Flag::CollisionEvent()
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		if (!IsFlag) {
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			Mario* Player = dynamic_cast<Mario*>(Ptr);
			Player->SetState(MarioState::End);
			IsFlag = true;
		}
	}
	if (IsEnd) {
		return;
	}
	std::vector<UCollision*> EResult;
	if (true == BottomCollision->CollisionCheck(MarioCollisionOrder::Player, EResult))
	{
		if (IsFlag) {
			UCollision* BCollision = EResult[0];
			AActor* Ptr = BCollision->GetOwner();
			Mario* Player = dynamic_cast<Mario*>(Ptr);
			Player->SetState(MarioState::EndMove);
			IsEnd = true;
		}
	}
}

