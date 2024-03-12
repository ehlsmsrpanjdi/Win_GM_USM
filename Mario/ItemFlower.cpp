#include "ItemFlower.h"

ItemFlower::ItemFlower() 
{
}

ItemFlower::~ItemFlower() 
{
}

void ItemFlower::BeginPlay()
{
	DirState = EActorDir::Right;
	SetName("Item");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Item);
	Renderer->SetImage("Item.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });

	State = ItemState::Flower;


	AnimationAuto(Renderer, "Idle", 2, 5, 0.2f, true);

	SetAnimation("Idle");

	BodyCollision = CreateCollision(MarioCollisionOrder::Item);
	BodyCollision->SetTransform({ { 0, 0 }, { 64, 64} });
}

