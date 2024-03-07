#include "Pipe.h"
#include "MarioHelper.h"
#include "Mario.h"
#include <EnginePlatform/EngineInput.h>


Pipe::Pipe()
{
}

Pipe::~Pipe()
{
}

void Pipe::BeginPlay()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Object);
	BodyCollision->SetTransform({ { 0,-5 } ,{32,128} });

	BodyRenderer = CreateImageRenderer(MarioRenderOrder::Cheat);
	BodyRenderer->SetTransform({ {0,0}, {128, 128} });
	BodyRenderer->SetImage("Pipe.png");
}

void Pipe::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		Mario* Player;
		UCollision* Collision = Result[0];
		Player = (Mario*)Collision->GetOwner();

		if (UEngineInput::IsDown(VK_DOWN) && Player->GetState() != MarioState::TelePorting) {
			MarioHelper::CameraOff = true;
			Player->SetState(MarioState::TelePorting);
			Player->SetAnimation("Idle");
		}

		else if(Player->GetState() == MarioState::TelePorting){
			if (TeleportTime >= 0) {
				TeleportTime -= _DeltaTime;
				Player->AddActorLocation(FVector::Down * 127 * _DeltaTime);
			}
			else {
				TeleportTime = 1.0f;
				Player->SetActorLocation(PlayerLocation);
				GetWorld()->SetCameraPos(CameraLocation);
				Player->SetState(MarioState::TelePortEnd);
			}
		}
	}
}

void Pipe::SetTotalLocation(FVector _PlayerLocation, FVector _CameraLocation)
{
	PlayerLocation = _PlayerLocation;
	CameraLocation = _CameraLocation;
}

