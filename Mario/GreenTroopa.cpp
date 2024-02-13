#include "GreenTroopa.h"

#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
GreenTroopa::GreenTroopa() 
{
}

GreenTroopa::~GreenTroopa() 
{
}

void GreenTroopa::BeginPlay()
{
	SetName("GreenTroopa");
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("GreenTroopa_Right.png");
	Renderer->SetTransform({ {0,0 }, { 256,256} });
	AnimationAuto(Renderer, "Idle", 0, 1, true, 0.2f);
	SetAnimation("Idle");
}

void GreenTroopa::Tick(float _DeltaTime)
{
	AutoMove(_DeltaTime);
}

