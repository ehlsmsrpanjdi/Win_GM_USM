#include "Coin.h"

Coin::Coin() 
{
}

Coin::~Coin() 
{
}

void Coin::BeginPlay()
{
	SetName("Coin");
	Renderer = CreateImageRenderer(MarioRenderOrder::Item);
	Renderer->SetImage("Coin.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });
	NoDir = true;
	AnimationAuto(Renderer, "Idle", 0, 3, 0.1f);

	SetAnimation("Idle");

	Destroy(0.5f);

}

void Coin::Tick(float _DeltaTime)
{
	UpSpeed += DownSpeed * _DeltaTime;
	AddActorLocation({0.f,UpSpeed * _DeltaTime});
}

