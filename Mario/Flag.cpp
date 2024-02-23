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
	SetName("Plag");
	Renderer = CreateImageRenderer(MarioRenderOrder::Item);
	Renderer->SetImage("Item.png");
	Renderer->SetTransform({ {0,0 }, { 128,640 } });


	BodyCollision = CreateCollision(MarioCollisionOrder::Item);
	BodyCollision->SetTransform({ { 0, -320 }, { 64, 640} });
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
		FVector CurPlayerLocation = Player->GetActorLocation();
		FVector CurLocation = GetActorLocation();

		if (CurPlayerLocation.Y > CurLocation.Y) {
			Player->SetState(MarioState::EndMove);
		}
		else {
			Player->SetState(MarioState::End);
		}

	}
}

