#include "Mario.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include "Fire.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>
#include "MarioHelper.h"
#include <string>
#include "PhysicsActor.h"


FVector Mario::PlayerLocation = {};

Mario::Mario()
{
	DirState = EActorDir::Right;
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
	AnimationAuto(Renderer, "Dead", 6, 6);

	BodyCollision = CreateCollision(MarioCollisionOrder::Player);
	BodyCollision->SetColType(ECollisionType::Rect);
	BodyCollision->SetTransform({ { 0,-32 }, { 64, 64 } });


	SetAnimation("Idle");
	SetState(MarioState::Idle);

}

void Mario::Tick(float _DeltaTime)
{
	PhysicsActor::Tick(_DeltaTime);

	PlayerLocation = GetActorLocation();

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
	DirCheck();
	switch (State)
	{
	case MarioState::None:
		break;
	case MarioState::Idle:
		GravityCheck(_DeltaTime);
		Idle(_DeltaTime);
		break;
	case MarioState::Move:
		GravityCheck(_DeltaTime);
		Move(_DeltaTime);
		break;
	case MarioState::Jump:
		Jump(_DeltaTime);
		break;
	case MarioState::DirChange:
		GravityCheck(_DeltaTime);
		DirChange(_DeltaTime);
		break;
	case MarioState::Interactive:
		Interactive(_DeltaTime);
		break;
	case MarioState::Dead:
		Dead(_DeltaTime);
		break;
	default:
		break;
	}

}



void Mario::AddSpeed(float _DeltaTime, FVector _FVector) {

	float NextFloatX = abs(CurSpeed.X + (_FVector.X * _DeltaTime));
	if (MaxSpeedX >= NextFloatX) {
		SpeedX.X += _FVector.X * _DeltaTime;
	}

	float NextFloatY = abs(CurSpeed.Y + (_FVector.Y * _DeltaTime));
	if (MaxSpeedY >= NextFloatY) {
		SpeedY.Y += _FVector.Y * _DeltaTime;
	}
}

void Mario::SubtractSpeed(float _DeltaTime, FVector _FVector)
{
	if (CurSpeedDir == -1) {
		SpeedX += (_FVector * _DeltaTime);
	}
	else if (CurSpeedDir == 1) {
		SpeedX -= (_FVector * _DeltaTime);
	}
}



void Mario::SetState(MarioState _State)
{

	if (State != _State || _State == MarioState::Interactive)
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
		case MarioState::Interactive:
			InteractiveStart();
			break;
		case MarioState::Dead:
			DeadStart();
			break;
		default:
			break;
		}
	}
	State = _State;
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
	SpeedY.Y = JumpPower;
	GravitySpeed.Y = 0;
	AddActorLocation({ 0.f,-4.f });
	SetAnimation("Jump");
}

void Mario::DirChangeStart()
{
	SetAnimation("DirChange");
}


void Mario::InteractiveStart()
{
	Jumping = true;
	GravitySpeed.Y = 0;
	SpeedY.Y = -500;
	SetAnimation("Jump");
}

void Mario::Idle(float _DeltaTime)
{

	ResultMove(_DeltaTime);


	if (0 == CurSpeedDir) {
		SpeedX.X = 0;
	}



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



	if (UEngineInput::IsDown(VK_SPACE) && false == Jumping) {
		SetState(MarioState::Jump);
		return;
	}


}

void Mario::DeadStart()
{
	GravitySpeed.Y = 0.f;
	SpeedX.X = 0.f;
	SpeedY.Y = -500.f;
	SetAnimation("Dead");
	BodyCollision->Destroy();
}

void Mario::Move(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE) && false == Jumping) {
		SetState(MarioState::Jump);
		return;
	}

	//	GravityCheck(_DeltaTime);

	if ((UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)) ||
		UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress(VK_RIGHT))
	{
		if (CurSpeedDir == 0) {
			SetState(MarioState::Idle);
			return;
		}
		SubtractSpeed(_DeltaTime, StopAccelerateX);
		ResultMove(_DeltaTime);
		return;
	}


	if (abs(CurSpeed.X) > 300) {
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

void Mario::Dead(float _DeltaTime) {

	if (DeadTime < 0.f) {
		GravitySpeed += MarioHelper::Gravity * _DeltaTime;
		ResultMove(_DeltaTime);
		Destroy(3.f);
	}
	else {
		DeadTime -= _DeltaTime;
	}
}

void Mario::Jump(float _DeltaTime)
{
	if (true == UEngineInput::IsUp(VK_SPACE) && CurSpeed.Y < 0.f) {
		SpeedY.Y = 0;
		GravitySpeed.Y = 0;
	}

	MoveFun(_DeltaTime, AccelerateX);
	GravityCheck(_DeltaTime);
	//GravityCheck(_DeltaTime);

	if (StopSpeed.Y == SpeedY.Y && StopSpeed.Y == GravitySpeed.Y) {
		if (abs(SpeedX.X) > 5) {
			SetState(MarioState::Move);
			Jumping = false;
			return;
		}
		else {
			SetState(MarioState::Idle);
			Jumping = false;
			return;
		}
	}
}

void Mario::DirChange(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE) && false == Jumping) {
		SetState(MarioState::Jump);
		return;
	}

	if (CurSpeedDir == 1) {
		if (UEngineInput::IsPress(VK_LEFT)) {
			SubtractSpeed(_DeltaTime, StopAccelerateX);
			ResultMove(_DeltaTime);
			return;
		}
		else if (UEngineInput::IsPress(VK_RIGHT)) {
			SetState(MarioState::Move);
			return;
		}
		else if (UEngineInput::IsFree(VK_LEFT)) {
			SubtractSpeed(_DeltaTime, StopAccelerateX);
			ResultMove(_DeltaTime);
			return;
		}
	}

	else if (CurSpeedDir == -1) {
		if (UEngineInput::IsPress(VK_RIGHT)) {
			SubtractSpeed(_DeltaTime, StopAccelerateX);
			ResultMove(_DeltaTime);
			return;
		}
		else if (UEngineInput::IsPress(VK_LEFT)) {
			SetState(MarioState::Move);
			return;
		}
		else if (UEngineInput::IsFree(VK_RIGHT)) {
			SubtractSpeed(_DeltaTime, StopAccelerateX);
			ResultMove(_DeltaTime);
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
	std::string Name = GetAnimationName(_Name);

	Renderer->ChangeAnimation(Name);
}


void Mario::MoveFun(float _DeltaTime, FVector _FVector)
{
	if (UEngineInput::IsPress(VK_LEFT) == true) {
		AddSpeed(_DeltaTime, -_FVector);
		SetAnimation(CurAnimationName);
		DirCheck();
		ResultMove(_DeltaTime);
		return;
	}

	if (UEngineInput::IsPress(VK_RIGHT) == true) {
		AddSpeed(_DeltaTime, _FVector);
		SetAnimation(CurAnimationName);
		ResultMove(_DeltaTime);
		return;
	}
	SetAnimation(CurAnimationName);
	ResultMove(_DeltaTime);
	return;
}

void Mario::Interactive(float _DeltaTime)
{
	Jumping = true;
	GravityCheck(_DeltaTime);
	MoveFun(_DeltaTime, AccelerateX);
	//	GravityCheck(_DeltaTime);

	if (StopSpeed.Y == SpeedY.Y && StopSpeed.Y == GravitySpeed.Y) {
		if (abs(SpeedX.X) > 5) {
			SetState(MarioState::Move);
			Jumping = false;
			return;
		}
		else {
			SetState(MarioState::Idle);
			Jumping = false;
			return;
		}
	}

}

bool Mario::LeftEdgeCheck()
{

	FVector CurLocation = GetActorLocation();
	int EdgeLocation_Left = static_cast<int>(CurLocation.X - 32.f);
	int EdgeLocation_Top = static_cast<int>(CurLocation.Y - 32.f);
	int EdgeLocation_Bottom = static_cast<int>(CurLocation.Y - 3.f);

	Color8Bit CheckColor_LeftTop = MarioHelper::ColMapImage->GetColor(EdgeLocation_Left, EdgeLocation_Top, Color8Bit::MagentaA);
	Color8Bit CheckColor_LeftBottom = MarioHelper::ColMapImage->GetColor(EdgeLocation_Left, EdgeLocation_Bottom, Color8Bit::MagentaA);

	bool FirstCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_LeftBottom);
	bool SecondCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_LeftTop);

	if (FirstCondition || SecondCondition) {
		AddActorLocation({ 0.5f, 0.f });
		SpeedX.X = 0;
		return false;
	}
	return true;
}

bool Mario::RightEdgeCheck()
{

	FVector CurLocation = GetActorLocation();
	int EdgeLocation_Right = static_cast<int>(CurLocation.X + 32.f);
	int EdgeLocation_Top = static_cast<int>(CurLocation.Y - 32.f);
	int EdgeLocation_Bottom = static_cast<int>(CurLocation.Y - 3.f);

	Color8Bit CheckColor_RightTop = MarioHelper::ColMapImage->GetColor(EdgeLocation_Right, EdgeLocation_Top, Color8Bit::MagentaA);
	Color8Bit CheckColor_RightBottom = MarioHelper::ColMapImage->GetColor(EdgeLocation_Right, EdgeLocation_Bottom, Color8Bit::MagentaA);

	bool FirstCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_RightBottom);
	bool SecondCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_RightTop);

	if (FirstCondition || SecondCondition) {
		AddActorLocation({ -0.5f, 0.f });
		SpeedX.X = 0;
		return false;
	}
	return true;
}

void Mario::DirCheck()
{
	EActorDir Dir = DirState;

	if (true == UEngineInput::IsPress(VK_LEFT) && false == UEngineInput::IsPress(VK_RIGHT)) {
		DirState = EActorDir::Left;
	}

	else if (true == UEngineInput::IsPress(VK_RIGHT) && false == UEngineInput::IsPress(VK_LEFT)) {
		DirState = EActorDir::Right;
	}

	if (true == Jumping) {
		DirState = Dir;
	}


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

void Mario::MarioCollisionEvent(float _DeltaTime)
{
	FVector ThisPosition = this->GetActorLocation();
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Block, Result))
	{
		UCollision* Collision = Result[0];
		FTransform CollisionTransform = Collision->GetActorBaseTransform();

		float LeftX = CollisionTransform.GetPosition().X - CollisionTransform.GetScale().hX();
		float RightX = CollisionTransform.GetPosition().X + CollisionTransform.GetScale().hX();
		float TopY = CollisionTransform.GetPosition().Y - CollisionTransform.GetScale().hY();
		float BottomY = CollisionTransform.GetPosition().Y + CollisionTransform.GetScale().hY();

		if (LeftX < ThisPosition.X + 24 && RightX > ThisPosition.X - 24) {
			if (TopY < ThisPosition.Y && 0 < (SpeedY.Y + GravitySpeed.Y) && TopY > ThisPosition.Y - 10) {
				GravitySpeed.Y = 0.f;
				SpeedY.Y = 0;
				IsCollision = true;
			}
   			else if ((SpeedY.Y + GravitySpeed.Y < 0) && BottomY < ThisPosition.Y - 32) {
				SpeedY.Y = 0;
			}
		}

		if (LeftX < ThisPosition.X + 28 && CurSpeedDir == 1) {
			if (TopY > ThisPosition.Y - 2 || BottomY < ThisPosition.Y - 64) {
				int a = 0;
			}
			else {
				SpeedX.X = 0;
			}
		}

		if (LeftX < ThisPosition.X - 28 && CurSpeedDir == -1) {
			if (TopY > ThisPosition.Y - 2 || BottomY < ThisPosition.Y - 64) {
				int a = 0;
			}
			else {
				SpeedX.X = 0;
			}
		}

	}
	else {
		IsCollision = false;
	}
}

void Mario::ResultMove(float _DeltaTime)
{
	if (1 == CurSpeedDir) {
		RightEdgeCheck();
	}
	else if (-1 == CurSpeedDir) {
		LeftEdgeCheck();
	}

	MarioCollisionEvent(_DeltaTime);

	CurSpeed = StopSpeed;
	CurSpeed += SpeedX;
	CurSpeed += SpeedY;
	CurSpeed += GravitySpeed;


	AddActorLocation(CurSpeed * _DeltaTime);
	SetActorCameraPos();
}