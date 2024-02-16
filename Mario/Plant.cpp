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
	AnimationAuto(Renderer, "Idle", 0, 1, false);
	SetAnimation("Idle");
}

void Plant::Tick(float _DeltaTime)
{

	StateUpdate(_DeltaTime);

	CollisionEvent(State);

}

void Plant::StateUpdate(float _DeltaTime)
{
}

void Plant::CollisionEvent(MonsterState _State)
{
}

