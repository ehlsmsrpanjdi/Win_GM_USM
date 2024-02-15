#include "CollisionActor.h"
#include <EngineCore\EngineResourcesManager.h>
#include <Mario/MarioHelper.h>
CollisionActor::CollisionActor()
{
}

CollisionActor::~CollisionActor()
{
}

void CollisionActor::SetRenderImage(std::string_view _MapImageName)
{
	Renderer->SetImage(_MapImageName);
	UWindowImage* Image = Renderer->GetImage();
	FVector ImageScale = Image->GetScale();
	Renderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void CollisionActor::SetColRenderImage(std::string_view _MapImageName)
{
	ColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = ColRenderer->GetImage();
	MarioHelper::ColMapImage = Image;
	FVector ImageScale = Image->GetScale();
	ColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void CollisionActor::SetCollisionActorImage(std::string_view _MapImageName)
{
	std::string Name = _MapImageName.data();

	SetRenderImage(Name + ".PNG");
	SetColRenderImage(Name + "_Col.PNG");
}

void CollisionActor::StateUpdate(float _DeltaTime)
{
}

void CollisionActor::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(GetOrder());
	ColRenderer = CreateImageRenderer(GetOrder());
	ColRenderer->SetActive(false);
}

void CollisionActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


	if (UEngineInput::IsDown('O'))
	{
		SwitchRender();
	}
}


void CollisionActor::SwitchRender()
{

	if (true == Renderer->IsActive())
	{
		Renderer->SetActive(false);
		ColRenderer->SetActive(true);
	}
	else
	{
		Renderer->SetActive(true);
		ColRenderer->SetActive(false);
	}

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
void CollisionActor::AnimationAuto(UImageRenderer* _Renderer, std::string _Name, int _Start, int _End, bool _DoubleWay, float _Time, bool _Routine)
{
	std::string CurName = GetName();
	if (_DoubleWay == false) {
		_Renderer->CreateAnimation(_Name, CurName + ".PNG", _Start, _End, _Time, _Routine);
		return;
	}
	_Renderer->CreateAnimation(_Name + "_Right", CurName + "_Right.PNG", _Start, _End, _Time, _Routine);
	_Renderer->CreateAnimation(_Name + "_Left", CurName + "_Left.PNG", _Start, _End, _Time, _Routine);
	return;
}

std::string CollisionActor::GetAnimationName(std::string _Name)
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

void CollisionActor::SetAnimation(std::string _Name)
{
	EActorDir Dir = DirState;

	std::string Name = GetAnimationName(_Name);

	Renderer->ChangeAnimation(Name);
}

bool CollisionActor::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);

	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(MarioHelper::Gravity * _DeltaTime);
		return true;
	}

	return false;
}

void CollisionActor::IsEdge(float _DeltaTime)
{


}
