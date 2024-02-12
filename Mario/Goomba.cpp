#include "Goomba.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"

Goomba::Goomba() 
{
}

Goomba::~Goomba() 
{
}

void Goomba::BeginPlay()
{
	SetName("Goomba");
	UImageRenderer* Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	AnimationAuto(Renderer, "Default" , 0, 1);
}

void Goomba::Tick(float _DeltaTime)
{
}

