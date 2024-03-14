#include "GameOverLogo.h"
#include <EngineCore/EngineCore.h>

GameOverLogo::GameOverLogo() 
{
}

GameOverLogo::~GameOverLogo() 
{
}

void GameOverLogo::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer();

	Renderer->SetImage("GameOver.png");
	// 이미지가 나올 위치
	float a = GEngine->MainWindow.GetWindowScale().hX();
	float  b = GEngine->MainWindow.GetWindowScale().hY();
	SetActorLocation({ a, b });
	Renderer->SetTransform({ {0,0}, {257 * 4, 267 * 4} });
}

