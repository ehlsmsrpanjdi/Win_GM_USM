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
	SetName("Mario");
	std::string test = GetName();
	Renderer = CreateImageRenderer(MarioRenderOrder::Player);
	Renderer->SetImage("TestPlayer_Right.png");
	Renderer->SetTransform({ {0,0}, {256, 256} });
	Renderer->CreateAnimation("Idle_Right", "TestPlayer_Right.png", 0, 0, 0.1f, false);
	Renderer->CreateAnimation("Move_Right", "TestPlayer_Right.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Jump_Right", "TestPlayer_Right.png", 5, 5, 0.1f, false);

	Renderer->CreateAnimation("Idle_Left", "TestPlayer_Left.png", 0, 0, 0.1f, false);
	Renderer->CreateAnimation("Move_Left", "TestPlayer_Left.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Jump_Left", "TestPlayer_Left.png", 5, 5, 0.1f, false);
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
	else {
		int a = 0;
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
	SetAnimation("Jump");
}

void Mario::Idle(float _DeltaTime)
{

	GravityCheck(_DeltaTime);


	if (true == UEngineInput::IsDown(VK_LEFT) || true == UEngineInput::IsDown(VK_RIGHT)) {
		SetState(EPlayState::Move);
	}

	if (true == UEngineInput::IsUp(VK_LEFT) || true == UEngineInput::IsUp(VK_RIGHT)) {
		SetState(EPlayState::Move);
	}



	if (UEngineInput::IsDown(VK_SPACE)) {
		SetState(EPlayState::Jump);
		return;
	}


}

void Mario::Move(float _DeltaTime)
{

	GravityCheck(_DeltaTime);


	if (UEngineInput::IsDown(VK_SPACE)) {
		SetState(EPlayState::Jump);
		return;
	}
	if (true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsPress(VK_RIGHT)) {
		NotMove(_DeltaTime);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT) == true) {
		AddSpeed(-AccelerateX * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT) == true) {
		AddSpeed(AccelerateX * _DeltaTime);
	}

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)) {
		NotMove(_DeltaTime);
		return;
	}

	if (true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsPress(VK_RIGHT)) {
		NotMove(_DeltaTime);
		return;
	}

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)) {
		NotMove(_DeltaTime);
		return;
	}

	SetAnimation("Move");
	AddActorLocation(CurSpeed * _DeltaTime);
	SetActorCameraPos();

}

void Mario::Jump(float _DeltaTime)
{



	if (UEngineInput::IsPress(VK_LEFT) == true) {
		AddSpeed(-AccelerateX * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT) == true) {
		AddSpeed(AccelerateX * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_SPACE) == true) {
		AddSpeed(-AccelerateY * _DeltaTime);
	}
	
	if (UEngineInput::IsUp(VK_SPACE) == true) {
		CurSpeed.Y = StopSpeed.Y;

	}
	if (UEngineInput::IsFree(VK_SPACE) == true) {
		GravityCheck(_DeltaTime);
	}
	
	SetAnimation("Jump");
	AddActorLocation(CurSpeed * _DeltaTime);
	SetActorCameraPos();





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
	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		Dir = EActorDir::Left;
	}
	if (UEngineInput::IsPress(VK_RIGHT) && UEngineInput::IsFree(VK_LEFT))
	{
		Dir = EActorDir::Right;
	}


	DirState = Dir;
	std::string Name = GetAnimationName(_Name);

	Renderer->ChangeAnimation(Name);
}

void Mario::NotMove(float _DeltaTime)
{
	//if (CurSpeed.X > 0.f) {
	//	AddSpeed(-AccelerateX * _DeltaTime);
	//}
	//else if (CurSpeed.X < 0.f) {
	//	AddSpeed(AccelerateX * _DeltaTime);
	//}


	if (CurSpeed.X > 0.f) {
		CurSpeed.X -= (AccelerateX.X * _DeltaTime);

	}
	else if (CurSpeed.X < 0.f) {
		CurSpeed.X += (AccelerateX.X * _DeltaTime);
	}

	if (CurSpeed.X < 10.f && CurSpeed.X > -10.f) {
		CurSpeed.X = 0;
		SetState(EPlayState::Idle);
	}
	AddActorLocation(CurSpeed * _DeltaTime);
	//float TempStopSpeed = (CurSpeed.X * _DeltaTime * 0.001f);
	SetActorCameraPos();

}


