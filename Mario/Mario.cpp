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
#include "BlockBase.h"
#include <EngineCore/EngineDebug.h>
#include <EnginePlatform/EngineSound.h>

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
	AnimationAuto(Renderer, "End", 7, 8);

	AnimationAuto(Renderer, "Bigger", 18, 19, 0.1f);
	AnimationAuto(Renderer, "Big_Smaller", 18, 19, 0.1f);
	AnimationAuto(Renderer, "Smaller", 18, 19, 0.1f);
	AnimationAuto(Renderer, "Big_Fire", 32, 33, 0.1f);
	AnimationAuto(Renderer, "Fire", 32, 33, 0.1f);
	AnimationAuto(Renderer, "Fire_Smaller", 32, 33, 0.1f);

	AnimationAuto(Renderer, "Big_Idle", 9, 9);
	AnimationAuto(Renderer, "Big_Move", 10, 12);
	AnimationAuto(Renderer, "Big_DirChange", 13, 13);
	AnimationAuto(Renderer, "Big_Crouch", 15, 15, 0.1f, false);
	AnimationAuto(Renderer, "Big_Jump", 14, 14);
	AnimationAuto(Renderer, "Big_End", 16, 17);

	AnimationAuto(Renderer, "Fire_Idle", 20, 20);
	AnimationAuto(Renderer, "Fire_Move", 21, 23);
	AnimationAuto(Renderer, "Fire_DirChange", 24, 24);
	AnimationAuto(Renderer, "Fire_Jump", 25, 25);
	AnimationAuto(Renderer, "Fire_End", 27, 28);
	AnimationAuto(Renderer, "Fire_Crouch", 26, 26, 0.1f, false);




	BodyCollision = CreateCollision(MarioCollisionOrder::Player);
	BodyCollision->SetColType(ECollisionType::Rect);

	switch (MarioHelper::MyMarioClass)
	{
	case MarioClass::Small:
		BodyCollision->SetTransform({ { 0,-32 }, { 56, 64 } });
		break;
	case MarioClass::Big:
		BodyCollision->SetTransform({ { 0,-64 }, { 56, 128} });
		break;
	case MarioClass::Fire:
		BodyCollision->SetTransform({ { 0,-64 }, { 56, 128} });
		break;
	default:
		break;
	}


	SetAnimation("Idle");
	SetState(MarioState::Idle);

}

void Mario::Tick(float _DeltaTime)
{
	const FVector  a = GEngine->MainWindow.GetMousePosition();
	UEngineDebug::DebugTextPrint(std::to_string(Mario::PlayerLocation.X) + "     " + std::to_string(Mario::PlayerLocation.Y), 24);
	UEngineDebug::DebugTextPrint(std::to_string(1 / _DeltaTime), 24);
	UEngineDebug::DebugTextPrint(std::to_string(GetWorld()->GetCameraPos().X), 24);

	MarioHelper::CameraX = GetWorld()->GetCameraPos().X;
	MarioHelper::WindowCenter = GEngine->MainWindow.GetWindowScale().X;

	MarioFall();

	if (UEngineInput::IsDown('J')) {
		Debug = true;
		GodTime = 1000.f;
	}

	if (UEngineInput::IsDown('K')) {
		Debug = false;
	}


	PhysicsActor::Tick(_DeltaTime);
	PlayerLocation = GetActorLocation();

	if (UEngineInput::IsPress('Z')) {
		JumpPower = -1000.f;
		AccelerateX = { 600.f,0.f,0.f,0.f };
		MaxSpeedX = 600.f;
	}
	else {
		JumpPower = -900.f;
		AccelerateX = { 400.f,0.f,0.f,0.f };
		MaxSpeedX = 400.f;
	}
	if (MarioHelper::MyMarioClass == MarioClass::Fire && UEngineInput::IsDown('Z') && AFire::FireCount < 2) {
		AFire* Fire = GetWorld()->SpawnActor<AFire>(MarioRenderOrder::Fire);
		Fire->SetActorLocation(FVector{ PlayerLocation.X, PlayerLocation.Y - 64 });
		BGMPlayer = UEngineSound::SoundPlay("FireBall.wav");
		Fire->SetDirState(DirState);
		++AFire::FireCount;
	}
	if (GodTime >= 0.f) {
		GodTime -= _DeltaTime;
	}

	if (Debug) {
		if (UEngineInput::IsPress(VK_RIGHT)) {
			AddActorLocation(FVector::Right * 1000 * _DeltaTime);
			GetWorld()->AddCameraPos(FVector::Right * 1000 * _DeltaTime);
		}
		if (UEngineInput::IsPress(VK_LEFT)) {
			AddActorLocation(FVector::Left * 1000 * _DeltaTime);
			GetWorld()->AddCameraPos(FVector::Left * 1000 * _DeltaTime);
		}
		if (UEngineInput::IsPress(VK_UP)) {
			AddActorLocation(FVector::Up * 1000 * _DeltaTime);
			GetWorld()->AddCameraPos(FVector::Up * 1000 * _DeltaTime);
		}
		if (UEngineInput::IsPress(VK_DOWN)) {
			AddActorLocation(FVector::Down * 1000 * _DeltaTime);
			GetWorld()->AddCameraPos(FVector::Down * 1000 * _DeltaTime);
		}
		return;
	}

	StateUpdate(_DeltaTime);

}

void Mario::SetActorCameraPos()
{
	if (!MarioHelper::CameraOff)
	{
		FVector CurPos = GetActorLocation();
		FVector CurCameraPos = GetWorld()->GetCameraPos();
		float WindowCenter = GEngine->MainWindow.GetWindowScale().hX();
		if (CurPos.X > WindowCenter + CurCameraPos.X) {
			GetWorld()->SetCameraPos({ CurPos.X - WindowCenter,CurCameraPos.Y });
		}
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
	case MarioState::Crouch:
		Crouch(_DeltaTime);
		break;
	case MarioState::CrouchJump:
		CrouchJump(_DeltaTime);
		break;
	case MarioState::Dead:
		Dead(_DeltaTime);
		break;
	case MarioState::End:
		End(_DeltaTime);
		break;
	case MarioState::EndMove:
		EndMove(_DeltaTime);
		break;
	case MarioState::Changing:
		Changing(_DeltaTime);
		break;
	case MarioState::TelePorting:
		TelePorting(_DeltaTime);
		break;
	case MarioState::TelePortEnd:
		TelePortEnding(_DeltaTime);
		break;
	case MarioState::EndingMove:
		EndingMove(_DeltaTime);
		break;
	case MarioState::Ending:
		Ending(_DeltaTime);
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
	else {
		if (CurSpeed.X < 0 && _FVector.X < 0) {
			SpeedX.X -= _FVector.X * _DeltaTime;
		}
		else if (CurSpeed.X > 0 && _FVector.X > 0)
			SpeedX.X -= _FVector.X * _DeltaTime;
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
	if (_State == MarioState::Dead) {
		if (GodTime >= 0.f) {
			return;
		}
	}

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
		case MarioState::Crouch:
			CrouchStart();
			break;
		case MarioState::CrouchJump:
			CrouchJumpStart();
			break;
		case MarioState::Dead:
			DeadStart();
			break;
		case MarioState::End:
			if (State == MarioState::EndMove) {
				return;
			}
			EndStart();
			break;
		case MarioState::EndMove:
			EndMoveStart();
			break;
		case MarioState::Changing:
			ChangingStart();
			break;
		case MarioState::TelePorting:
			TelePortingStart();
			break;
		case MarioState::TelePortEnd:
			TelePortEndingStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Mario::SetMarioClassState(MarioClass _MarioClass)
{
	if (MarioHelper::MyMarioClass == _MarioClass) {
		return;
	}
	ChangeTime = 1.f;
	switch (_MarioClass)
	{
	case MarioClass::Small:
		GodTime = 2.f;
		SetAnimation("Smaller");
		BGMPlayer = UEngineSound::SoundPlay("PipeTravel.wav");
		BodyCollision->SetTransform({ { 0,-32 }, { 56, 64 } });
		break;
	case MarioClass::Big:
		SetAnimation("Bigger");
		BodyCollision->SetTransform({ { 0,-64 }, { 56, 128 } });
		break;
	case MarioClass::Fire:
		SetAnimation("Fire");
		BodyCollision->SetTransform({ { 0,-64 }, { 56, 128 } });
		break;
	default:
		break;
	}
	MarioHelper::MyMarioClass = _MarioClass;
	SetState(MarioState::Changing);
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
	if (MarioHelper::MyMarioClass == MarioClass::Small) {
		BGMPlayer = UEngineSound::SoundPlay("SmallJump.wav");

	}
	else {
		BGMPlayer = UEngineSound::SoundPlay("SuperJump.wav");

	}
	if (PrevState == MarioState::Jump) {
		Jumping = true;
		SpeedY.Y = 0;
		GravitySpeed.Y = 0;
		AddActorLocation({ 0.f,-4.f });
		SetAnimation("Jump");
		PrevState = MarioState::None;
	}
	else {
		Jumping = true;
		if (GravitySpeed.Y < 10) {
			SpeedY.Y = JumpPower;
		}
		else {
			return;
		}
		GravitySpeed.Y = 0;
		AddActorLocation({ 0.f,-4.f });
		SetAnimation("Jump");
	}
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

void Mario::CrouchStart()
{
	BodyCollision->SetTransform({ { 0,-32 }, { 56, 64 } });
	SetAnimation("Crouch");
}

void Mario::CrouchJumpStart()
{
	BodyCollision->SetTransform({ { 0,-32 }, { 56, 64 } });
	SpeedY.Y = 0;
	GravitySpeed.Y = 0;
	SpeedY.Y = JumpPower;
	AddActorLocation(FVector::Up * 5);
}

void Mario::Idle(float _DeltaTime)
{
	ResultMove(_DeltaTime);

	if (0 == CurSpeedDir) {
		SpeedX.X = 0;
	}

	if (UEngineInput::IsPress(VK_DOWN) && !(MarioClass::Small == MarioHelper::MyMarioClass)) {
		SetState(MarioState::Crouch);
		return;
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

void Mario::EndStart()
{
	DirState = EActorDir::Right;
	SetAnimation("End");
}

void Mario::EndMoveStart()
{
	DirState = EActorDir::Left;
	SetAnimation("End");
	float CurPosX = GetActorLocation().X + 64.f;
	float CurPosY = GetActorLocation().Y;
	SetActorLocation({ CurPosX , CurPosY });
}

void Mario::Move(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_SPACE) && false == Jumping) {
		SetState(MarioState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_DOWN) && !(MarioClass::Small == MarioHelper::MyMarioClass)) {
		SetState(MarioState::Crouch);
		return;
	}

	GravityCheck(_DeltaTime);

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
		float Y = SpeedY.Y + GravitySpeed.Y;
		AddActorLocation(FVector{ 0.f,Y * _DeltaTime });
		if (ChangeLevelTime <= 0) {
			ChangeLevelTime = 2.5f;
			MarioHelper::MarioLife -= 1;
			GEngine->ChangeLevel("Loading");
		}
		else {
			ChangeLevelTime -= _DeltaTime;
		}
	}
	else {
		DeadTime -= _DeltaTime;
	}

}

void Mario::End(float _DeltaTime)
{
	float pos = 100.f * _DeltaTime;
	AddActorLocation({ 0.f, pos });

	if (UEngineInput::IsDown('W')) {
		SetState(MarioState::EndMove);
	}
}

void Mario::ChangingStart()
{
	GetWorld()->SetOtherTimeScale(static_cast<int>(MarioRenderOrder::Player), 0.0f);
	PrevState = State;
	ChangeTime = 1.f;
}

void Mario::TelePortingStart()
{

	SpeedX.X = 0;
	SpeedY.Y = 0;
	switch (MarioHelper::MyMarioClass)
	{
	case MarioClass::Small:
		BodyCollision->SetTransform({ { 0,-32 }, { 56, 64 } });
		break;
	case MarioClass::Big:
	case MarioClass::Fire:
		BodyCollision->SetTransform({ { 0,-64 }, { 56, 128} });
		break;
	default:
		break;
	}
}

void Mario::TelePortEndingStart()
{
	BGMPlayer = UEngineSound::SoundPlay("PipeTravel.wav");
	SetAnimation("Idle");
}

void Mario::EndMove(float _DeltaTime)
{
	if (EndTime >= 0) {
		EndTime -= _DeltaTime;
		return;
	}
	DirState = EActorDir::Right;
	SetAnimation("Move");
	SpeedX.X = 100.f;
	GravityCheck(_DeltaTime);
	AddActorLocation(SpeedX * _DeltaTime);
	AddActorLocation(GravitySpeed * _DeltaTime);
	SetActorCameraPos();
}
void Mario::Jump(float _DeltaTime)
{
	if (true == UEngineInput::IsUp(VK_SPACE) && CurSpeed.Y < 0.f) {
		SpeedY.Y = 0;
		GravitySpeed.Y = 10;
	}

	MoveFun(_DeltaTime, AccelerateX);
	GravityCheck(_DeltaTime);

	if (StopSpeed.Y == SpeedY.Y &&  10 > abs(GravitySpeed.Y)) {
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
	switch (MarioHelper::MyMarioClass)
	{
	case MarioClass::Small:
		break;
	case MarioClass::Big:
		Name = "Big_" + Name;
		break;
	case MarioClass::Fire:
		Name = "Fire_" + Name;
		break;
	default:
		break;
	}

	if (Name._Equal("Big_Bigger_Left") || Name._Equal("Big_Bigger_Right")) {
		return;
	}

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

void Mario::Crouch(float _DeltaTime)
{
	GravityCheck(_DeltaTime);

	SetAnimation("Crouch");

	SpeedX.X -= SpeedX.X * _DeltaTime * 4;
	if (abs(SpeedX.X) < 10) {
		SpeedX.X = 0;
	}
	ResultMove(_DeltaTime);
	if (UEngineInput::IsDown(VK_SPACE)) {
		SetState(MarioState::CrouchJump);
		return;
	}

	if (UEngineInput::IsFree(VK_DOWN)) {
		if (abs(CurSpeed.X) < 3) {
			SetState(MarioState::Idle);
			BodyCollision->SetTransform({ { 0,-64 }, { 56, 128} });
		}
		else {
			SetState(MarioState::Move);
			BodyCollision->SetTransform({ { 0,-64 }, { 56, 128} });
		}
	}
}

void Mario::CrouchJump(float _DeltaTime)
{
	ResultMove(_DeltaTime);
	GravityCheck(_DeltaTime);

	SetAnimation("Crouch");

	if (true == UEngineInput::IsUp(VK_SPACE) && CurSpeed.Y < 0.f) {
		SpeedY.Y = 0;
		GravitySpeed.Y = 0;
	}

	if (UEngineInput::IsFree(VK_DOWN)) {
		SetState(MarioState::Idle);
		BodyCollision->SetTransform({ { 0,-64 }, { 56, 128} });
	}

	if (UEngineInput::IsFree(VK_SPACE)) {
		if (StopSpeed.Y == SpeedY.Y && StopSpeed.Y == GravitySpeed.Y) {
			SetState(MarioState::Crouch);
			Jumping = false;
			return;
		}
	}
}

bool Mario::LeftEdgeCheck()
{

	FVector CurLocation = GetActorLocation();

	if (MarioHelper::LeftCheck(CurLocation)) {
		AddActorLocation({ 0.5f, 0.f });
		SpeedX.X = 0;
		return false;
	}
	return true;

	int EdgeLocation_Left = static_cast<int>(CurLocation.X - 32.f);
	int EdgeLocation_Top = static_cast<int>(CurLocation.Y - 32.f);
	int EdgeLocation_Bottom = static_cast<int>(CurLocation.Y - 3.f);

	Color8Bit CheckColor_LeftTop = MarioHelper::ColMapImage->GetColor(EdgeLocation_Left, EdgeLocation_Top, Color8Bit(0,0,0,0));
	Color8Bit CheckColor_LeftBottom = MarioHelper::ColMapImage->GetColor(EdgeLocation_Left, EdgeLocation_Bottom - 2, Color8Bit(0, 0, 0, 0));

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
	if (MarioHelper::RightCheck(CurLocation)) {
		AddActorLocation({ -0.5f, 0.f });
		SpeedX.X = 0;
		return false;
	}
	return true;



	int EdgeLocation_Right = static_cast<int>(CurLocation.X + 32.f);
	int EdgeLocation_Top = static_cast<int>(CurLocation.Y - 32.f);
	int EdgeLocation_Bottom = static_cast<int>(CurLocation.Y - 3.f);

	Color8Bit CheckColor_RightTop = MarioHelper::ColMapImage->GetColor(EdgeLocation_Right, EdgeLocation_Top, Color8Bit(0, 0, 0, 0));
	Color8Bit CheckColor_RightBottom = MarioHelper::ColMapImage->GetColor(EdgeLocation_Right, EdgeLocation_Bottom - 2, Color8Bit(0, 0, 0, 0));

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

void Mario::MarioFall()
{
	FVector CurLocation = GetActorLocation();
	Color8Bit FallCheck = MarioHelper::ColMapImage->GetColor(CurLocation.iX(), CurLocation.iY(), Color8Bit(0, 0, 0, 0));
	if (Color8Bit(255, 255, 0, 0) == FallCheck) {
		MarioHelper::MyMarioClass = MarioClass::Small;
		SetState(MarioState::Dead);
	}
}

void Mario::MarioCollisionEvent(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Block, Result))
	{
		for (UCollision* ResultCollision : Result) {
			BlockBase* Block = static_cast<BlockBase*>(ResultCollision->GetOwner());
			FTransform MarioTransform = BodyCollision->GetActorBaseTransform();
			FTransform ResultTransform = ResultCollision->GetActorBaseTransform();

			bool Beside = (MarioTransform.GetPosition().X > ResultTransform.Left() && MarioTransform.GetPosition().X < ResultTransform.Right());

			if (MarioTransform.Top() + 30 > ResultTransform.Bottom()) {
				if (MarioState::EndMove != State && Beside && (SpeedY.Y + GravitySpeed.Y) < -10) {
					Block->SetBoxState(BlockState::Interactive);
				}
				SpeedY.Y = 0.f;
				SetActorLocation({ MarioTransform.GetPosition().X,ResultTransform.Bottom() + MarioTransform.GetScale().Y });
			}

			else if (MarioTransform.Bottom() > ResultTransform.Top() + 10) {

				if (CurSpeedDir == 1) {
					SpeedX.X = 0;
					AddActorLocation(FVector::Left);
				}
				else if (CurSpeedDir == -1) {
					SpeedX.X = 0;
					AddActorLocation(FVector::Right);
				}
			}
			else {
				SpeedY.Y = 0;
				GravitySpeed.Y = 0;
				SetActorLocation({ MarioTransform.GetPosition().X,ResultTransform.Top() });
			}
		}
	}
}

void Mario::Hit()
{
	if (GodTime >= 0.f) {
		return;
	}

	switch (MarioHelper::MyMarioClass)
	{
	case MarioClass::Small:
		SetState(MarioState::Dead);
		break;
	case MarioClass::Big:
		SetMarioClassState(MarioClass::Small);
		break;
	case MarioClass::Fire:
		SetMarioClassState(MarioClass::Small);
		break;
	default:
		break;
	}
}

void Mario::Changing(float _DeltaTime)
{
	if (ChangeTime >= 0.f) {
		ChangeTime -= _DeltaTime;
	}
	else if (ChangeTime < 0) {
		SetState(PrevState);
		GetWorld()->SetAllTimeScale(1.0f);
	}
}

void Mario::EndingMove(float _DeltaTime)
{
	DirState = EActorDir::Right;
	SetAnimation("Move");
	SpeedX.X = 100.f;
	GravityCheck(_DeltaTime);
	AddActorLocation(SpeedX * _DeltaTime);
	AddActorLocation(GravitySpeed * _DeltaTime);
	SetActorCameraPos();
}

void Mario::Ending(float _DeltaTime)
{
	SetAnimation("Idle");
	if (EndingTime >= 0) {
		EndingTime -= _DeltaTime;
	}
	else {
		GEngine->ChangeLevel("Title");
		EndingTime = 16.f;
	}
}
void Mario::TelePorting(float _DeltaTime)
{
}
void Mario::TelePortEnding(float _DeltaTime)
{
	FVector CurLocation = GetActorLocation();

	Color8Bit Color_Left = MarioHelper::ColMapImage->GetColor(CurLocation.iX(), CurLocation.iY(), Color8Bit(0, 0, 0, 0));

	if (MarioHelper::BottomCheck({ CurLocation.X,CurLocation.Y - 1 })) {
		AddActorLocation(FVector::Up * _DeltaTime * 50);
		CurLocation.Y -= 1;
	}
	else {
		SetState(MarioState::Idle);
	}
}
bool Mario::TopCheck()
{
	FVector CurLocation = GetActorLocation();
	float TopSize = -128.f;
	if (MarioHelper::MyMarioClass == MarioClass::Small) {
		TopSize = -64.f;
	}
	int TopLocation = static_cast<int>(CurLocation.Y + TopSize);

	Color8Bit TopCheckColor = MarioHelper::ColMapImage->GetColor(CurLocation.iX(), TopLocation, Color8Bit(0, 0, 0, 0));

	while (Color8Bit(255, 0, 255, 0) == TopCheckColor) {
		SpeedY.Y = 0.f;
		GravitySpeed.Y = 0.f;
		AddActorLocation(FVector::Down);
		TopLocation += 1;
		TopCheckColor = MarioHelper::ColMapImage->GetColor(CurLocation.iX(), TopLocation, Color8Bit(0, 0, 0, 0));
	}
	return false;
}


void Mario::ResultMove(float _DeltaTime)
{
	if (1 == CurSpeedDir) {
		RightEdgeCheck();
	}
	else if (-1 == CurSpeedDir) {
		LeftEdgeCheck();
	}
	TopCheck();


	MarioCollisionEvent(_DeltaTime);

	CurSpeed = StopSpeed;
	CurSpeed += SpeedX;
	CurSpeed += SpeedY;
	CurSpeed += GravitySpeed;

	FVector CurLocation = GetActorLocation();
	float CameraX = GetWorld()->GetCameraPos().X;

	if (CurLocation.X - 32.f + CurSpeed.X * _DeltaTime < CameraX) {
		CurSpeed.X = 0;
	}
	AddActorLocation(CurSpeed * _DeltaTime);

	while (MarioHelper::BottomCheck(GetActorLocation() + FVector{ 0,-1 })) {
		AddActorLocation(FVector::Up);
	}
	SetActorCameraPos();
}