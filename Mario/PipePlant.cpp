#include "PipePlant.h"

PipePlant::PipePlant() 
{
}

PipePlant::~PipePlant() 
{
}

void PipePlant::StateUpdate(float _DeltaTime)
{
	std::vector<UCollision*> MResult;
	if (CheatCollision->CollisionCheck(MarioCollisionOrder::Player, MResult) && !Start) {
		BodyCollision->ActiveOff();
		Start = true;
	}

	if (!Start) {
		return;
	}

	if (StartLocation.X == 0 && StartLocation.Y == 0) {
		StartLocation = GetActorLocation();
		NextLocation = StartLocation + FVector{ 0.f, -96.f };
	}

	FVector CurLocation = GetActorLocation();

	switch (PlantState)
	{
	case 1:
		{
			TotalMove += _DeltaTime;
			std::vector<UCollision*> Result;
			if (CheatCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
				return;
			}
			if (TotalMove >= 2.0f) {
				PlantState++;
				TotalMove = 0.f;
			}
		}
		break;
	case 2:
		AddActorLocation(FVector::Up * _DeltaTime * SpawnTime);
		if (CurLocation.Y < NextLocation.Y) {
			PlantState++;
		}
	break;
	case 3:
		BodyCollision->ActiveOn();
		TotalMove += _DeltaTime;
		if (TotalMove >= 2.0f) {
			PlantState++;
			TotalMove = 0.f;
		}
		break;
	case 4:
		AddActorLocation(FVector::Down * _DeltaTime * SpawnTime);
		if (CurLocation.Y > StartLocation.Y) {
			PlantState = 1;
		}
		break;
	default:
		break;
	}
}

