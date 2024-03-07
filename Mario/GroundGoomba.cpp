#include "GroundGoomba.h"

GroundGoomba::GroundGoomba() 
{
}

GroundGoomba::~GroundGoomba() 
{
}

void GroundGoomba::BeginPlay()
{
	MonsterBase::BeginPlay();
	SetName("BlackGoomba");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("BlackGoomba.png");
	Renderer->SetTransform({ {0,0 }, { 384,384} });
	AnimationAuto(Renderer, "Idle", 0, 1, 0.2f);
	SetAnimation("Idle");

	AnimationAuto(Renderer, "Dead", 2, 2);
}

