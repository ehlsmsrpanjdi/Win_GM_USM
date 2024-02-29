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

		if (UEngineInput::IsDown(VK_DOWN) && Player->GetState() == MarioState::Idle && IsTeleporting != true) {
			Player->SetState(MarioState::TelePorting);
			MarioHelper::TeleportLocation = PlayerLocation;
			MarioHelper::TeleportCameraLocation = CameraLocation;
			MarioHelper::IsGround = IsGround;
			IsTeleporting = true;
		}

		if (IsTeleporting == true) {
			if (TeleportTime >= 0) {
				TeleportTime -= _DeltaTime;
				Player->AddActorLocation(FVector::Down * 100 * _DeltaTime);
			}
			else {
				IsTeleporting = false;
				TeleportTime = 2.0f;
			}
		}
	}
}

void Pipe::SetTotalLocation(FVector _PlayerLocation, FVector _CameraLocation, bool _IsGround)
{
	PlayerLocation = _PlayerLocation;
	CameraLocation = _CameraLocation;
	IsGround = _IsGround;
}

