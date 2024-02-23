#include "MushRoom.h"
#include "Mario.h"

MushRoom::MushRoom()
{
}

MushRoom::~MushRoom()
{
}

void MushRoom::BeginPlay()
{
	DirState = EActorDir::Right;
	SetName("Item");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Item);
	Renderer->SetImage("Item.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });

	State = ItemState::MushRoom;


	AnimationAuto(Renderer, "Idle", 0, 0, 0.1f, false);

	SetAnimation("Idle");

	BodyCollision = CreateCollision(MarioCollisionOrder::Item);
	BodyCollision->SetTransform({ { 0, -32 }, { 64, 64} });
}