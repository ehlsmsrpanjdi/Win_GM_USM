#include "MarioBlock.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"

MarioBlock::MarioBlock()
{
}

MarioBlock::~MarioBlock()
{
}

void MarioBlock::BeginPlay()
{
	NoDir = true;
	HaveItem = ItemState::MushRoom;
	ItemCount = 1;
	SetName("MarioBlock");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("MarioBlock.png");
	Renderer->SetTransform({ {0,0 }, { 1024,1024 } });
	AnimationAuto(Renderer, "ItemBlock", 0, 3, 0.2f);
	SetAnimation("ItemBlock");

	AnimationAuto(Renderer, "Default", 4, 4, 0.1f, false);
}

void MarioBlock::BlockInit()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Block);
	BodyCollision->SetTransform({ { 0, -32 }, { 64, 64} });

	BoxState = BlockState::ItemBlock;
	StartState = BlockState::ItemBlock;
}

