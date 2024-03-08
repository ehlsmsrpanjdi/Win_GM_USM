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
	BodyCollision->SetTransform({ { -16,0 } ,{128,32} });

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

		if (UEngineInput::IsDown(VK_RIGHT) && Player->GetState() != MarioState::TelePorting) {
			MarioHelper::CameraOff = true;
			Player->SetState(MarioState::TelePorting);
			Player->SetAnimation("Move");
		}
		else if (Player->GetState() == MarioState::TelePorting) {
			if (TeleportTime >= 0) {
				TeleportTime -= _DeltaTime;
				Player->AddActorLocation(FVector::Right * 63 * _DeltaTime);
			}
			else {
				TeleportTime = 1.0f;
				Player->SetActorLocation(PlayerLocation);
				GetWorld()->SetCameraPos(CameraLocation);
				Player->SetState(MarioState::TelePortEnd);
				MarioHelper::CameraOff = false;
			}
		}
	}
}


void LeftPipe::SetTotalLocation(FVector _PlayerLocation, FVector _CameraLocation)
{
	PlayerLocation = _PlayerLocation;
	CameraLocation = _CameraLocation;
}

