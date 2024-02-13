#include "Plant.h"

#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
Plant::Plant() 
{
}

Plant::~Plant() 
{
}

void Plant::BeginPlay()
{
	SetName("Plant");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("Plant.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });
	AnimationAuto(Renderer, "Default", 0, 1, false, 0.2f);
	SetAnimation("Default");
}

