#include "MovingBlock.h"
#include "MarioHelper.h"
#include "Mario.h"

MovingBlock::MovingBlock()
{
}

MovingBlock::~MovingBlock()
{
}

void MovingBlock::BeginPlay()
{
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	SetName("MovingBlock");
	Renderer->SetImage(GetName() + ".png");
	Renderer->SetTransform({ { 0,0 },{ 196,48} });
	BodyCollision = CreateCollision(MarioCollisionOrder::MovingBox);
	BodyCollision->SetTransform({ { 0,0 }, { 196,44} });
}

void MovingBlock::Tick(float _DeltaTime)
{
	Moving(_DeltaTime);
	CollisionEvent(_DeltaTime);
}

void MovingBlock::MovingBlockInit(FVector _StartPos, FVector _EndPos, bool _IsTelePort)
{
	StartPos = _StartPos;
	EndPos = _EndPos;
	TelePort = _IsTelePort;
}

void MovingBlock::Moving(float _DeltaTime)
{
	FVector DirPos = (EndPos - StartPos);
	FVector DirPosNormal = DirPos.Normalize2DReturn();
	FVector CurAcc = DirPosNormal* _DeltaTime* Speed;
	if (abs(CurSpeed.X + CurAcc.X) <= MaxSpeed && abs(CurSpeed.Y + CurAcc.Y) <= MaxSpeed) {
	CurSpeed += CurAcc;
	}
	AddActorLocation(CurSpeed * _DeltaTime);
	FVector CurLocation = GetActorLocation();
	float SubX = EndPos.X - CurLocation.X;
	float SubY = EndPos.Y - CurLocation.Y;
	if (TelePort == true) {
		if (abs(SubX) + abs(SubY) < 10) {
			SetActorLocation(StartPos);
		}
	}
	else {
		if (abs(SubX) + abs(SubY) < 10) {
			FVector TempLocation = StartPos;
			StartPos = EndPos;
			EndPos = TempLocation;
		}
	}

	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		Mario* Player = static_cast<Mario*>(Result[0]->GetOwner());
		FTransform ResultTransform = BodyCollision->GetActorBaseTransform();
		FTransform MarioTransform = Result[0]->GetActorBaseTransform();
		FVector MarioPos = MarioTransform.GetPosition();
		FVector BoxPos = ResultTransform.GetPosition();
		if (MarioPos.X > ResultTransform.Left() && MarioPos.X < ResultTransform.Right()) {
			if (MarioPos.Y < ResultTransform.Bottom()) {
				Player->SetActorLocation({ Player->GetActorLocation().X, ResultTransform.Top() + 2 });
				Player->SpeedY.Y = 0;
				Player->GravitySpeed.Y = 0;
				Player->AddActorLocation(DirPosNormal * _DeltaTime * Speed);
			}
			else {
				Player->GravitySpeed.Y = 10;
				Player->SpeedY.Y = 0;
			}
		}
		else if (MarioPos.X + 24 > ResultTransform.Right()) {
			Player->AddActorLocation(FVector::Right);
			Player->SpeedX.X = 0;
		}
		else if (MarioPos.X - 24 < ResultTransform.Left()) {
			Player->AddActorLocation(FVector::Left);
			Player->SpeedX.X = 0;
		}
	}
}

void MovingBlock::CollisionEvent(float _DeltaTime)
{

}
