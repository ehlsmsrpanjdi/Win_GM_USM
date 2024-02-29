#include "LeftPipe.h"
#include "MarioHelper.h"
#include "Mario.h"
#include <EnginePlatform/EngineInput.h>


LeftPipe::LeftPipe()
{
}

LeftPipe::~LeftPipe()
{
}

void LeftPipe::BeginPlay()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Object);
	BodyCollision->SetTransform({ { 0,0 } ,{128,32} });

	BodyRenderer = CreateImageRenderer(MarioRenderOrder::Cheat);
	BodyRenderer->SetTransform({ {0,0}, {128, 128} });
	BodyRenderer->SetImage("LeftPipe.png");
}

void LeftPipe::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		Mario* Player;
		UCollision* Collision = Result[0];
		Player = (Mario*)Collision->GetOwner();

		if (UEngineInput::IsDown(VK_RIGHT) && Player->GetState() == MarioState::Move && IsTeleporting != true) {
			MarioHelper::TeleportLocation = PlayerLocation;
			MarioHelper::TeleportCameraLocation = CameraLocation;
			MarioHelper::IsGround = IsGround;
			Player->SetState(MarioState::TelePortEnd);
			IsTeleporting = true;
		}

		if (IsTeleporting == true) {
			if (TeleportTime >= 0) {
				TeleportTime -= _DeltaTime;
				Player->AddActorLocation(FVector::Right * 100 * _DeltaTime);
			}
			else {
				IsTeleporting = false;
				TeleportTime = 1.0f;
				MarioHelper::IsGround = false;
				Player->SetActorLocation(MarioHelper::TeleportLocation);
			}
		}
	}
}

void LeftPipe::SetTotalLocation(FVector _PlayerLocation, FVector _CameraLocation, bool _IsGround)
{
	PlayerLocation = _PlayerLocation;
	CameraLocation = _CameraLocation;
	IsGround = _IsGround;
}

