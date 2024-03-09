#include "PhysicsActor.h"
#include <EngineCore\EngineResourcesManager.h>
#include <Mario/MarioHelper.h>
#include "Mario.h"


PhysicsActor::PhysicsActor()
{
}

PhysicsActor::~PhysicsActor()
{
}


void PhysicsActor::Tick(float _DeltaTime)
{

}


/// <summary>
/// 
/// </summary>
/// <param name="_Renderer"></param>
/// <param name="_Name"></param>
/// <param name="_Start"></param>
/// <param name="_End"></param>
/// <param name="_Time">0.1f</param>
/// <param name="_DoubleWay">true</param>
/// <param name="_Routine">true</param>
void PhysicsActor::AnimationAuto(UImageRenderer* _Renderer, std::string _Name, int _Start, int _End, float _Time, bool _Routine)
{
	std::string CurName = GetName();
	if (NoDir) {
		_Renderer->CreateAnimation(_Name, CurName + ".PNG", _Start, _End, _Time, _Routine);
		return;
	}
	_Renderer->CreateAnimation(_Name + "_Right", CurName + "_Right.PNG", _Start, _End, _Time, _Routine);
	_Renderer->CreateAnimation(_Name + "_Left", CurName + "_Left.PNG", _Start, _End, _Time, _Routine);
	return;
}


std::string PhysicsActor::GetAnimationName(std::string _Name)
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

	if (NoDir) {
		DirName = "";
	}

	CurAnimationName = _Name;

	return _Name + DirName;
}

void PhysicsActor::SetAnimation(std::string _Name)
{
	std::string Name = GetAnimationName(_Name);
	Renderer->ChangeAnimation(Name);
}

bool PhysicsActor::GravityCheck(float _DeltaTime)
{

	FVector CurLocation = GetActorLocation();
	GravitySpeed += MarioHelper::Gravity * _DeltaTime;

	Color8Bit Color_Right = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX() + 28, GetActorLocation().iY(), Color8Bit(0, 0, 0, 0));
	Color8Bit Color_Left = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX() - 28, GetActorLocation().iY(), Color8Bit(0, 0, 0, 0));

	while (MarioHelper::BottomCheck({ CurLocation.X,CurLocation.Y - 1 })) {
		AddActorLocation(FVector::Up);
		CurLocation.Y -= 1;
	}

	if (Color_Right == Color8Bit(255, 0, 255, 0) || Color_Left == Color8Bit(255, 0, 255, 0))
	{
		GravitySpeed = StopSpeed;
		SpeedY = StopSpeed;
		return false;
	}


	return true;
}


void PhysicsActor::ResultMove(float _DeltaTime)
{
	CurSpeed = StopSpeed;
	CurSpeed += SpeedX;
	CurSpeed += SpeedY;
	CurSpeed += GravitySpeed;
	AddActorLocation(CurSpeed * _DeltaTime);
}
