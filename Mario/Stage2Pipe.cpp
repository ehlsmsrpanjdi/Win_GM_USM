#include "Stage2Pipe.h"
#include "MarioHelper.h"
#include "Mario.h"

Stage2Pipe::Stage2Pipe()
{
}

Stage2Pipe::~Stage2Pipe()
{
}

void Stage2Pipe::BeginPlay()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Object);
	BodyCollision->SetTransform({ { 0,0 } ,{1280,32} });

	BodyRenderer = CreateImageRenderer(MarioRenderOrder::Cheat);
	BodyRenderer->SetTransform({ {0,0}, {134, 128} });
	BodyRenderer->SetImage("LeftPipe.png");

	TeleportCollision = CreateCollision(MarioCollisionOrder::Object);
	TeleportCollision->SetTransform({ { 0,0 }, { 134,128 } });
}

void Stage2Pipe::Tick(float _DeltaTime)
{

	std::vector<UCollision*> MResult;
	if (true == TeleportCollision->CollisionCheck(MarioCollisionOrder::Player, MResult))
	{
		Mario* Player;
		UCollision* Collision = MResult[0];
		Player = (Mario*)Collision->GetOwner();
		if (TeleportTime >= 0) {
			if (!SoundOnce) {
			BGMPlayer = UEngineSound::SoundPlay("PipeTravel.wav");
			SoundOnce = true;
			}
			TeleportTime -= _DeltaTime;
			Player->AddActorLocation(FVector::Right * 63 * _DeltaTime);
		}
		else {
			BGMPlayer = UEngineSound::SoundPlay("PipeTravel.wav");
			TeleportTime = 1.0f;
			Player->SetActorLocation(PlayerLocation);
			GetWorld()->SetCameraPos(CameraLocation);
			Player->SetState(MarioState::TelePortEnd);
			MarioHelper::CameraOff = false;
		}
		return;
	}

	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		Mario* Player;
		UCollision* Collision = Result[0];
		Player = (Mario*)Collision->GetOwner();
		Player->SetState(MarioState::TelePorting);
		Player->AddActorLocation(FVector::Right * _DeltaTime * 100);
		Player->SetAnimation("Move");
	}

}

