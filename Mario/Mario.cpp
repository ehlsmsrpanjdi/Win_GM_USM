#include "Mario.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include "Fire.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>
#include "MarioHelper.h"

Mario::Mario()
{
}

Mario::~Mario()
{
}

void Mario::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(MarioRenderOrder::Player);
	Renderer->SetImage("TestPlayer_Right.png");
	Renderer->SetTransform({ {0,0}, {256, 256} });
	Renderer->CreateAnimation("Idle_Right", "TestPlayer_Right.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Move_Right", "TestPlayer_Right.png", 1, 3, 0.1f, true);

	Renderer->CreateAnimation("Idle_Left", "TestPlayer_Left.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "TestPlayer_Left.png", 1, 3, 0.1f, true);
	SetAnimation("Idle");
	SetState(EPlayState::Idle);

}

void Mario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);

}

void Mario::SetActorCameraPos()
{
	FVector CurPos = GetActorLocation();
	FVector CurCameraPos = GetWorld()->GetCameraPos();
	float WindowCenter = GEngine->MainWindow.GetWindowScale().hX();
	if (CurPos.X > WindowCenter + CurCameraPos.X) {
		GetWorld()->SetCameraPos({ CurPos.X - WindowCenter,CurCameraPos.Y });
	}
}

void Mario::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::None:
		
		break;
	case EPlayState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayState::Move:
		Move(_DeltaTime);
		break;
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	default:
		break;
	}

	GravityCheck(_DeltaTime);

}



void Mario::AddSpeed(FVector _FVector) {

	if (MaxSpeedX >= CurSpeed.X + _FVector.X && -MaxSpeedX <= CurSpeed.X + _FVector.X) {
		CurSpeed.X += _FVector.X;
	}

	if (MaxSpeedY >= CurSpeed.Y + _FVector.Y && -MaxSpeedY <= CurSpeed.Y + _FVector.Y) {
		CurSpeed.Y += _FVector.Y;
	}
}

void Mario::SetState(EPlayState _State)
{

	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Move:
			MoveStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;


}

bool Mario::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * _DeltaTime * MarioHelper::Gravity);
	}
	return false;
}

void Mario::IdleStart()
{
	SetAnimation("Idle");
}

void Mario::MoveStart()
{
	SetAnimation("Move");
}

void Mario::JumpStart()
{
	//SetAnimation("Move");
}

void Mario::Idle(float _DeltaTime)
{
	if (true == EngineInput::IsDown(VK_LEFT) || true == EngineInput::IsDown(VK_RIGHT)) {
		SetState(EPlayState::Move);
	}



}

void Mario::Move(float _DeltaTime)
{

	if (true == EngineInput::IsFree(VK_LEFT) && EngineInput::IsFree(VK_RIGHT))
	{
		SetState(EPlayState::Idle);
		return;
	}


	
}

void Mario::Jump(float _DeltaTime)
{
}

std::string Mario::GetAnimationName(std::string _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + DirName;
}


void Mario::SetAnimation(std::string _Name)
{
	EActorDir Dir = DirState;
	if (EngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}
	if (EngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}

	DirState = Dir;
	std::string Name = GetAnimationName(_Name);

	Renderer->ChangeAnimation(Name);
}
