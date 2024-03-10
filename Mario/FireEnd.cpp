#include "FireEnd.h"

FireEnd::FireEnd() 
{
}

FireEnd::~FireEnd() 
{
}

void FireEnd::BeginPlay()
{
	BGMPlayer = UEngineSound::SoundPlay("Interactive.wav");
	NoDir = true;
	AActor::BeginPlay();
	SetName("FireEnd");
	Renderer = CreateImageRenderer(MarioRenderOrder::Fire);
	Renderer->SetImage("FireEnd.png");
	Renderer->SetTransform({ {0,0}, {256, 256} });

	AnimationAuto(Renderer, "Idle", 0, 2);
	Destroy(0.3f);
	Renderer->ChangeAnimation("Idle");
}

void FireEnd::Tick(float _DeltaTime)
{
}

