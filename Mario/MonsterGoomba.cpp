#include "MonsterGoomba.h"

MonsterGoomba::MonsterGoomba() 
{
}

MonsterGoomba::~MonsterGoomba() 
{
}

void MonsterGoomba::BeginPlay()
{
	SetName("Goomba");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("Goomba.png");
	Renderer->SetTransform({ {0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 0, 1, 0.2f);
	SetAnimation("Idle");

	AnimationAuto(Renderer, "Dead", 2, 2);

	BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,-24 }, { 64, 64} });

	State = MonsterState::Idle;
}
