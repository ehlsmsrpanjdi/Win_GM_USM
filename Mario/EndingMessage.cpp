#include "EndingMessage.h"
#include "MarioHelper.h"
#include "Mario.h"

EndingMessage::EndingMessage()
{
}

EndingMessage::~EndingMessage()
{
	BGMPlayer.Off();
}

void EndingMessage::BeginPlay()
{
	EndingMessageBox = CreateImageRenderer(MarioRenderOrder::UI);
	EndingMessageBox->SetImage("EndingMessage.png");
	EndingMessageBox->SetTransform({ { 0,0 },{768,320} });

	EndingMessageBoxCheat = CreateImageRenderer(MarioRenderOrder::UI);
	EndingMessageBoxCheat->SetImage("EndingMessage_Cheat.png");
	EndingMessageBoxCheat->SetTransform({ { 0,0 },{768,320} });

	EndingMessageBoxCollision = CreateCollision(MarioCollisionOrder::Object);
	EndingMessageBoxCollision->SetTransform({ {78,0},{100,1000} });
}

void EndingMessage::Tick(float _DeltaTime)
{
	CollisionEvent(_DeltaTime);

	if (IsEnd) {
		if (NextPageTime >= 0) {
			NextPageTime -= _DeltaTime;
		}
		else {
			NextPageTime = 2.0f;
			FVector Scale = EndingMessageBoxCheat->GetTransform().GetScale();
			FVector Pos = EndingMessageBoxCheat->GetTransform().GetPosition();
			Pos.Y += 32.f;
			Scale.Y -= 64.f;
			EndingMessageBoxCheat->SetTransform({ {Pos},{Scale} });
		}
	}
}

void EndingMessage::CollisionEvent(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == EndingMessageBoxCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		BGMPlayer = UEngineSound::SoundPlay("Ending.mp3");
		Mario* Player = (Mario*)Result[0]->GetOwner();
		Player->SetState(MarioState::Ending);
		IsEnd = true;
		EndingMessageBoxCollision->Destroy();
	}
}

