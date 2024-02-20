#include "MarioBrick.h"

MarioBrick::MarioBrick() 
{
	NoDir = true;
}

MarioBrick::~MarioBrick() 
{
}

void MarioBrick::BeginPlay()
{
	SetName("MarioBrick");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("MarioBrick.png");
	Renderer->SetTransform({ {0,400 }, { 1024,1024 } });
	AnimationAuto(Renderer, "Brick", 0, 0, 0.1f, false);
	SetAnimation("Brick");

	AnimationAuto(Renderer, "None", 4, 4, 0.1f, false);

	BodyCollision = CreateCollision(MarioCollisionOrder::Block);
	BodyCollision->SetTransform({ { 0, 368 }, { 64, 64} });

	State = BlockState::Brick;
}