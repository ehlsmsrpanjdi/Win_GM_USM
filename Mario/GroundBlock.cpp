#include "GroundBlock.h"

GroundBlock::GroundBlock() 
{
}

GroundBlock::~GroundBlock() 
{
}

void GroundBlock::BeginPlay()
{
	NoDir = true;
	HaveItem = ItemState::MushRoom;
	ItemCount = 1;
	SetName("GroundBlock");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("GroundBlock.png");
	Renderer->SetTransform({ {0,0 }, { 1024,1024 } });
	AnimationAuto(Renderer, "ItemBlock", 0, 3, 0.2f);
	SetAnimation("ItemBlock");

	AnimationAuto(Renderer, "Default", 4, 4, 0.1f, false);
}

