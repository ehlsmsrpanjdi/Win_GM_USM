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

void CollisionActor::BeginPlay()
{
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

