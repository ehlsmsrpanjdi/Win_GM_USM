#include "EndingDoor.h"
#include "MarioHelper.h"
#include "Mario.h"

EndingDoor::EndingDoor() 
{
}

EndingDoor::~EndingDoor() 
{
}

void EndingDoor::BeginPlay()
{
	DoorCollision = CreateCollision(MarioCollisionOrder::Object);
	DoorCollision->SetTransform({ {0,0},{200,200} });
}

void EndingDoor::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == DoorCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		Mario* Player = (Mario*)Result[0]->GetOwner();
		Player->SetState(MarioState::Ending);
	}
}

