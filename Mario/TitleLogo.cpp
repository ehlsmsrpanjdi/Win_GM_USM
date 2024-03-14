#include "TitleLogo.h"
#include <EngineCore/EngineCore.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer();

	Renderer->SetImage("Title.png");
	float a = GEngine->MainWindow.GetWindowScale().hX();
	float  b = GEngine->MainWindow.GetWindowScale().hY();
	SetActorLocation({a, b });
	Renderer->SetTransform({ {0,0}, {257* 4, 267*4} });

}

