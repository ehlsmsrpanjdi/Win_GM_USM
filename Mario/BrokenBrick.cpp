#include "BrokenBrick.h"

BrokenBrick::BrokenBrick() 
{
}

BrokenBrick::~BrokenBrick() 
{
}

void BrokenBrick::BeginPlay()
{
	NoDir = true;
	AActor::BeginPlay();
	SetName("BrokenBrick");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("BrokenBrick.png");
	Renderer->SetTransform({ {0,0}, {32, 32} });

	AnimationAuto(Renderer, "Idle", 0, 3, 0.1f, true);


	SetAnimation("Idle");
	Destroy(3.f);
}

void BrokenBrick::Tick(float _DeltaTime)
{
	GravitySpeed += MarioHelper::Gravity * _DeltaTime;
	SpeedY.Y = -600.f;
	SpeedX.X = 200 * static_cast<int>(DirState);
	ResultMove(_DeltaTime);
}

