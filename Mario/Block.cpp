#include "Block.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"
#include "PhysicsActor.h"
Block::Block()
{
	NoDir = true;
}

Block::~Block()
{
}

void Block::BeginPlay()
{
	SetName("Block");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("Block.png");
	Renderer->SetTransform({ {0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 0, 1, false, 0.2f);
	SetAnimation("Idle");


	BodyCollision = CreateCollision(MarioCollisionOrder::Block);
	BodyCollision->SetTransform({ { 0,-24 }, { 64, 64} });

}

void Block::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	BoxCollisionEvent(State);

}

void Block::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case BlockState::Item:
		break;
	case BlockState::None:
		break;
	default:
		break;
	}
}

void Block::SetBoxState(BlockState _BlockState)
{
	switch (State)
	{
	case BlockState::Item:
		ItemStart();
		break;
	case BlockState::None:
		NoneStart();
		break;
	default:
		break;
	}
}

void Block::BoxCollisionEvent(BlockState _BlockState)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Mario* Player = dynamic_cast<Mario*>(Ptr);
		FVector CurPlayerLocation = Player->GetActorLocation();

		if (nullptr == Player)
		{
			MsgBoxAssert("터져야겠지....");
		}
		FVector CurLocation = GetActorLocation();
		return;
	}
}

void Block::ItemStart()
{

}

void Block::NoneStart()
{

	//SetAnimation("");
}

