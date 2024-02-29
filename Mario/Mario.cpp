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

MarioClass Mario::MyMarioClass = MarioClass::Small;
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

	//MushRoomRenderer = CreateImageRenderer(MarioRenderOrder::Player);
	//MushRoomRenderer->SetImage("Mario_Right.png");
	//MushRoomRenderer->SetTransform({ {0,0}, {256, 256} });


	AnimationAuto(Renderer, "Big_Idle", 9, 9);
	AnimationAuto(Renderer, "Big_Move", 10, 12);
	AnimationAuto(Renderer, "Big_DirChange", 13, 13);
	AnimationAuto(Renderer, "Big_Jump", 14, 14);
	AnimationAuto(Renderer, "Big_End", 16, 17);

	AnimationAuto(Renderer, "Fire_Idle", 20, 20);
	AnimationAuto(Renderer, "Fire_Move", 21, 23);
	AnimationAuto(Renderer, "Fire_DirChange", 24, 24);
	AnimationAuto(Renderer, "Fire_Jump", 25, 25);
	AnimationAuto(Renderer, "Fire_End", 27, 28);





	BodyCollision = CreateCollision(MarioCollisionOrder::Player);
	BodyCollision->SetColType(ECollisionType::Rect);
	BodyCollision->SetTransform({ { 0,-32 }, { 56, 64 } });

	SetAnimation("Idle");
	SetState(MarioState::Idle);

}

void Mario::Tick(float _DeltaTime)
{
	UEngineDebug::DebugTextPrint(std::to_string(Mario::PlayerLocation.X) + "     " + std::to_string(Mario::PlayerLocation.Y), 24);
	UEngineDebug::DebugTextPrint(std::to_string(GetWorld()->GetCameraPos().X), 24);

	if (UEngineInput::IsDown('J')) {
		AddActorLocation(FVector::Right * 400);
		GetWorld()->SetCameraPos(FVector::Right * 400);
		GodTime = 1000.f;
	}

	if (UEngineInput::IsDown('K')) {
		AddActorLocation(FVector::Up * 200);
		SetState(MarioState::TelePorting);
	}

	if (UEngineInput::IsDown('H')) {
		MarioHelper::LevelEnd = true;
	}

	//if (UEngineInput::IsDown('R')) {
	//	FVector CurPos = GetActorLocation();
	//	float WindowCenter = GEngine->MainWindow.GetWindowScale().hX();
	//	FVector CurCameraPos = GetWorld()->GetCameraPos();
	//	GetWorld()->SetCameraPos({ CurPos.X - WindowCenter,CurCameraPos.Y + 100 });
	//}
	//if (UEngineInput::IsDown('E')) {
	//	FVector CurPos = GetActorLocation();
	//	float WindowCenter = GEngine->MainWindow.GetWindowScale().hX();
	//	FVector CurCameraPos = GetWorld()->GetCameraPos();
	//	GetWorld()->SetCameraPos({ CurPos.X + 100 ,CurCameraPos.Y});
	//}

	PhysicsActor::Tick(_DeltaTime);

	PlayerLocation = GetActorLocation();

	if (MyMarioClass == MarioClass::Fire && UEngineInput::IsDown('Z') && AFire::FireCount < 2) {
		AFire* Fire = GetWorld()->SpawnActor<AFire>(MarioRenderOrder::Fire);
		Fire->SetActorLocation(FVector{ PlayerLocation.X, PlayerLocation.Y - 64 });
		Fire->SetDirState(DirState);
		++AFire::FireCount;
	}

	if (ChangeTime >= 0.f) {
		ChangeTime -= _DeltaTime;
	}
	if (GodTime >= 0.f) {
		GodTime -= _DeltaTime;
	}

	StateUpdate(_DeltaTime);

}

void Mario::SetActorCameraPos()
{
	if (!MarioHelper::IsGround)
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
		Teleporting(_DeltaTime);
		break;
	case MarioState::TelePortEnd:
		TeleportEnd(_DeltaTime);
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
			TeleportingStart();
			break;
		case MarioState::TelePortEnd:
			TeleportEndStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Mario::SetMarioClassState(MarioClass _MarioClass)
{
	if (MyMarioClass == _MarioClass) {
		return;
	}
	ChangeTime = 1.f;
	switch (_MarioClass)
	{
	case MarioClass::Small:
		GodTime = 2.f;
		SetAnimation("Smaller");
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
	MyMarioClass = _MarioClass;
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
		SpeedY.Y = JumpPower;
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

void Mario::TeleportingStart()
{
	TeleportingTime = 1.0f;
}

void Mario::TeleportEndStart()
{
	TeleportingTime = 1.0f;
	SpeedX.X = 0;
	SpeedY.Y = 0;
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
}
void Mario::Jump(float _DeltaTime)
{
	if (true == UEngineInput::IsUp(VK_SPACE) && CurSpeed.Y < 0.f) {
		SpeedY.Y = 0;
		GravitySpeed.Y = 0;
	}

	MoveFun(_DeltaTime, AccelerateX);
	GravityCheck(_DeltaTime);

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
	switch (MyMarioClass)
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

	Color8Bit CheckColor_LeftTop = MarioHelper::ColMapImage->GetColor(EdgeLocation_Left, EdgeLocation_Top, Color8Bit::MagentaA);
	Color8Bit CheckColor_LeftBottom = MarioHelper::ColMapImage->GetColor(EdgeLocation_Left, EdgeLocation_Bottom - 2, Color8Bit::MagentaA);

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

	Color8Bit CheckColor_RightTop = MarioHelper::ColMapImage->GetColor(EdgeLocation_Right, EdgeLocation_Top, Color8Bit::MagentaA);
	Color8Bit CheckColor_RightBottom = MarioHelper::ColMapImage->GetColor(EdgeLocation_Right, EdgeLocation_Bottom - 2, Color8Bit::MagentaA);

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
	std::vector<UCollision*> Result;
	IsCollision = false;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Block, Result))
	{
		IsCollision = false;
		for (UCollision* ResultCollision : Result) {
			//UCollision* ResultCollision = Result[0];
			BlockBase* Block = static_cast<BlockBase*>(ResultCollision->GetOwner());
			FTransform MarioTransform = BodyCollision->GetActorBaseTransform();
			FTransform ResultTransform = ResultCollision->GetActorBaseTransform();


			if (MarioTransform.Top() + 10 > ResultTransform.Bottom()) {
				if (MarioState::EndMove != State) {
					Block->SetBoxState(BlockState::Interactive);
				}
				SpeedY.Y = 0.f;
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
				IsCollision = true;
			}
		}
	}
}

void Mario::Hit()
{
	if (GodTime >= 0.f) {
		return;
	}

	switch (MyMarioClass)
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
	if (ChangeTime <= 0) {
		SetState(PrevState);
		GetWorld()->SetAllTimeScale(1.0f);
	}
}

void Mario::Teleporting(float _DeltaTime)
{
	if (TeleportingTime >= 0) {
		TeleportingTime -= _DeltaTime;
	}
	else {
		GetWorld()->SetCameraPos(MarioHelper::TeleportCameraLocation);
		SetActorLocation(MarioHelper::TeleportLocation);
		TeleportingTime = 1.0f;
		SetState(MarioState::Idle);
	}
}

void Mario::TeleportEnd(float _DeltaTime)
{
	if (TeleportingTime >= 0) {
		TeleportingTime -= _DeltaTime;
	}
	else {
		if (!GravityCheck(_DeltaTime)) {
			GetWorld()->SetCameraPos(MarioHelper::TeleportCameraLocation);
			/*SetActorLocation(MarioHelper::TeleportLocation);*/
			AddActorLocation(FVector::Up * _DeltaTime * 50);
		}
		else {
			SetState(MarioState::Idle);
		}
	}
}


void Mario::MarioChange(bool _Positive)
{
	if (_Positive) {
		switch (MyMarioClass)
		{
		case MarioClass::Small:
			break;
		case MarioClass::Big:
			break;
		case MarioClass::Fire:
			break;
		default:
			break;
		}
	}
	else {
		switch (MyMarioClass)
		{
		case MarioClass::Small:
			break;
		case MarioClass::Big:
			break;
		case MarioClass::Fire:
			break;
		default:
			break;
		}
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