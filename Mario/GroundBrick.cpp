#include "GroundBrick.h"


GroundBrick::GroundBrick() 
{
	IsGround = true;
}

GroundBrick::~GroundBrick() 
{
}

void GroundBrick::BeginPlay()
{
	NoDir = true;
	StartState = BlockState::Brick;
	SetName("GroundBrick");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("GroundBrick.png");
	Renderer->SetTransform({ {0,0 }, { 1024,1024 } });
	AnimationAuto(Renderer, "Brick", 0, 0, 0.1f, false);
	SetAnimation("Brick");

	AnimationAuto(Renderer, "Default", 4, 4, 0.1f, false);
}

