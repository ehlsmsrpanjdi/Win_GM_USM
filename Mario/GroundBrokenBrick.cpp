#include "GroundBrokenBrick.h"

GroundBrokenBrick::GroundBrokenBrick() 
{
}

GroundBrokenBrick::~GroundBrokenBrick() 
{

}

void GroundBrokenBrick::BeginPlay()
{
	NoDir = true;
	AActor::BeginPlay();
	SetName("GroundBrokenBrick");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("GroundBrokenBrick.png");
	Renderer->SetTransform({ {0,0}, {32, 32} });

	AnimationAuto(Renderer, "Idle", 0, 3, 0.1f, true);


	SetAnimation("Idle");
	Destroy(3.f);
}

void GroundBrokenBrick::Tick(float _DeltaTime)
{
	GravitySpeed += MarioHelper::Gravity * _DeltaTime;
	SpeedY.Y = -600.f;
	SpeedX.X = 200 * static_cast<int>(DirState);
	ResultMove(_DeltaTime);
}

