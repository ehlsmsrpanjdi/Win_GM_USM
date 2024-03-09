#include "RedTroopa.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"
#include "MonsterBase.h"

RedTroopa::RedTroopa() 
{
}

RedTroopa::~RedTroopa() 
{
}

void RedTroopa::BeginPlay()
{
	MonsterBase::BeginPlay();
	SetName("RedTroopa");
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("RedTroopa_Right.png");
	Renderer->SetTransform({ {0,0 }, { 512,512} });
	AnimationAuto(Renderer, "Idle", 0, 1, 0.2f);
	SetAnimation("Idle");
	AnimationAuto(Renderer, "Crouch", 4, 4);
	AnimationAuto(Renderer, "Fly", 2, 3, 0.2f);
}

