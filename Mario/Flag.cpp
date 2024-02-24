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
	Renderer = CreateImageRenderer(MarioRenderOrder::Item);
	Renderer->SetImage("Flag.png");
	Renderer->SetTransform({ {0,0 }, { 64,688 } });


	BodyCollision = CreateCollision(MarioCollisionOrder::Item);
	BodyCollision->SetTransform({ { 0, 0 }, { 16, 688} });
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
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Mario* Player = dynamic_cast<Mario*>(Ptr);
		float CurPlayerLocation = Player->GetActorLocation().Y;
		float CurLocation	 = GetActorLocation().Y + 344.f;

		if (CurPlayerLocation > CurLocation) {
			Player->SetState(MarioState::EndMove);
		}
		else {
			Player->SetState(MarioState::End);
		}

	}
}

