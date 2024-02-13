#include "Koopa.h"

#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
Koopa::Koopa() 
{
}

Koopa::~Koopa() 
{
}

void Koopa::BeginPlay()
{
	SetName("Goomba");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("Goomba.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });
	AnimationAuto(Renderer, "Default", 0, 1, false, 0.2f);
	SetAnimation("Default");
}

