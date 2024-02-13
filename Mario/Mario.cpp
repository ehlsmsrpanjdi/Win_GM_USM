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
	Renderer = CreateImageRenderer(MarioRenderOrder::Player);
	Renderer->SetImage("Mario_Right.png");
	Renderer->SetTransform({ {0,0}, {256, 256} });

	AnimationAuto(Renderer, "Idle", 0, 0);
	AnimationAuto(Renderer, "Move", 1, 3);
	AnimationAuto(Renderer, "DirChange", 4, 4);
	AnimationAuto(Renderer, "Jump", 5, 5);


	SetAnimation("Idle");
	SetState(MarioState::Idle);

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
	//if (UEngineInput::IsDown('x') || UEngineInput::IsDown('X')) {
	//	AccelerateX *= 2.f;
	//	MaxSpeedX *= 2.f;
	//}
	//if (UEngineInput::IsUp('x') || UEngineInput::IsUp('X')) {
	//	AccelerateX.X /= 2.f;
	//	MaxSpeedX /= 2.f;
	//}


	switch (State)
	{
	case MarioState::None:
		break;
	case MarioState::Idle:
		Idle(_DeltaTime);
		break;
	case MarioState::Move:
		Move(_DeltaTime);
		break;
	case MarioState::Jump:
		Jump(_DeltaTime);
		break;
	case MarioState::DirChange:
		DirChange(_DeltaTime);
		break;
	case MarioState::NotMove:
		NotMove(_DeltaTime);
		break;
	default:
		break;
	}

}



void Mario::AddSpeed(float _DeltaTime, FVector _FVector) {

	float NextFloatX = abs(CurSpeed.X + (_FVector.X * _DeltaTime));
	if (MaxSpeedX >= NextFloatX) {
		CurSpeed.X += _FVector.X * _DeltaTime;
	}

	float NextFloatY = abs(CurSpeed.Y + (_FVector.Y * _DeltaTime));
	if (MaxSpeedY >= NextFloatY) {
		CurSpeed.Y += _FVector.Y * _DeltaTime;
	}
	AddActorLocation(CurSpeed * _DeltaTime);
	SetActorCameraPos();
}

void Mario::SubtractSpeed(float _DeltaTime, FVector _FVector)
{
	if (CurSpeedDir == -1) {
		CurSpeed += (_FVector * _DeltaTime);
	}
	else if (CurSpeedDir == 1) {
		CurSpeed -= (_FVector * _DeltaTime);
	}
	AddActorLocation(CurSpeed * _DeltaTime);
	SetActorCameraPos();
}



void Mario::SetState(MarioState _State)
{

	if (State != _State)
	{
		switch (_State)
		{
		case MarioState::Idle:
			IdleStart();
			break;
		case MarioState::Move:
			MoveStart();
			break;
		case MarioState::Jump:
			JumpStart();
			break;
		case MarioState::DirChange:
			DirChangeStart();
			break;
		case MarioState::NotMove:
			NotMoveStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

bool Mario::GravityCheck(float _DeltaTime)
{
	//Color8Bit Color = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);

	//if (Color != Color8Bit(255, 0, 255, 0))
	//{
	//	AddSpeed(_DeltaTime, MarioHelper::Gravity);
	//}
	//else {
	//	CurSpeed.Y = 0;
	//	Jumping = false;
	//	AddSpeed(_DeltaTime, MarioHelper::Gravity);
	//}


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
	Jumping = true;
	CurSpeed.Y = JumpPower;
	SetAnimation("Jump");
}

void Mario::DirChangeStart()
{
	SetAnimation("DirChange");
}

void Mario::NotMoveStart()
{
}

void Mario::Idle(float _DeltaTime)
{

	GravityCheck(_DeltaTime);

	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress(VK_RIGHT)) {
		return;
	}

	if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT)) {
		SetState(MarioState::Move);
		return;
	}

	if (true == UEngineInput::IsUp(VK_LEFT) || true == UEngineInput::IsUp(VK_RIGHT)) {
		SetState(MarioState::Move);
		return;
	}



	if (UEngineInput::IsDown(VK_SPACE)) {
		SetState(MarioState::Jump);
		return;
	}


}

void Mario::Move(float _DeltaTime)
{

	GravityCheck(_DeltaTime);

	//if (UEngineInput::IsDown(VK_SPACE)) {
	//	SetState(MarioState::Jump);
	//	return;
	//}

	if ((UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)) ||
		UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress(VK_RIGHT))
	{
		CurSpeedDirCheck();
		if (CurSpeedDir == 0) {
			SetState(MarioState::Idle);
			return;
		}
		SubtractSpeed(_DeltaTime, StopAccelerateX);

		return;
	}


	if (abs(CurSpeed.X) > 300) {
		CurSpeedDirCheck();
		if (UEngineInput::IsPress(VK_LEFT) && CurSpeedDir == 1) {
			SetState(MarioState::DirChange);
			return;
		}
		if (UEngineInput::IsPress(VK_RIGHT) && CurSpeedDir == -1) {
			SetState(MarioState::DirChange);
			return;
		}
	}
	MoveFun(_DeltaTime, AccelerateX);
}

void Mario::Jump(float _DeltaTime)
{

	if (true == UEngineInput::IsUp(VK_SPACE)) {
		Jumping = false;
		CurSpeed.Y = 0;
	}
	GravityCheck(_DeltaTime);

}

void Mario::DirChange(float _DeltaTime)
{
	CurSpeedDirCheck();

	if (CurSpeedDir == 1) {
		if (UEngineInput::IsPress(VK_LEFT)) {
			SubtractSpeed(_DeltaTime, StopAccelerateX);
			return;
		}
		else if (UEngineInput::IsPress(VK_RIGHT)) {
			SetState(MarioState::Move);
			return;
		}
		else if (UEngineInput::IsFree(VK_LEFT)) {
			SubtractSpeed(_DeltaTime, StopAccelerateX);
			return;
		}
	}

	else if (CurSpeedDir == -1) {
		if (UEngineInput::IsPress(VK_RIGHT)) {
			SubtractSpeed(_DeltaTime, StopAccelerateX);
			return;
		}
		else if (UEngineInput::IsPress(VK_LEFT)) {
			SetState(MarioState::Move);
			return;
		}
		else if (UEngineInput::IsFree(VK_RIGHT)) {
			SubtractSpeed(_DeltaTime, StopAccelerateX);
			return;
		}
	}

	else {
		SetState(MarioState::Idle);
		return;
	}

}


void Mario::SetAnimation(std::string _Name)
{
	EActorDir Dir = DirState;
	if ((UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)) ||
		(UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsUp(VK_RIGHT)))
	{
		Dir = EActorDir::Left;
	}
	if ((UEngineInput::IsPress(VK_RIGHT) && UEngineInput::IsFree(VK_LEFT)) ||
		(UEngineInput::IsPress(VK_RIGHT) && UEngineInput::IsUp(VK_LEFT)))
	{
		Dir = EActorDir::Right;
	}



	DirState = Dir;
	std::string Name = GetAnimationName(_Name);
	std::string a =  GetName();


	Renderer->ChangeAnimation(Name);
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

void Mario::NotMove(float _DeltaTime)
{


	if (CurSpeed.X > 0.f) {
		CurSpeed.X -= (AccelerateX.X * _DeltaTime);

	}

	else if (CurSpeed.X < 0.f) {
		CurSpeed.X += (AccelerateX.X * _DeltaTime);
	}

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsPress(VK_RIGHT)) {
		if (CurSpeed.X < 0) {
			SetState(MarioState::DirChange);
			return;
		}
	}

	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)) {
		if (CurSpeed.X > 0) {
			SetState(MarioState::DirChange);
			return;
		}

	}


	if (CurSpeed.X < 10.f && CurSpeed.X > -10.f) {
		CurSpeed.X = 0;
		SetState(MarioState::Idle);
	}
	AddActorLocation(CurSpeed * _DeltaTime);
	//float TempStopSpeed = (CurSpeed.X * _DeltaTime * 0.001f);
	SetActorCameraPos();

}

void Mario::MoveFun(float _DeltaTime, FVector _FVector)
{
	if (UEngineInput::IsPress(VK_LEFT) == true) {
		AddSpeed(_DeltaTime, -_FVector);
		SetAnimation(CurAnimationName);
		return;
	}

	if (UEngineInput::IsPress(VK_RIGHT) == true) {
		AddSpeed(_DeltaTime, _FVector);
		SetAnimation(CurAnimationName);
		return;
	}
}

void Mario::CurSpeedDirCheck()
{
	if (CurSpeed.X > MinSpeed) {
		CurSpeedDir = 1;
	}

	else if (CurSpeed.X < -MinSpeed) {
		CurSpeedDir = -1;
	}
	else {
		CurSpeedDir = 0;
	}

}



