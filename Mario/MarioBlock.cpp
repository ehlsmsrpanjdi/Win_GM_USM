#include "MarioBlock.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"
#include "PhysicsActor.h"
MarioBlock::MarioBlock()
{
	NoDir = true;
}

MarioBlock::~MarioBlock()
{
}

void MarioBlock::BeginPlay()
{
	SetName("MarioBlock");
	Renderer = CreateImageRenderer(MarioRenderOrder::Block);
	Renderer->SetImage("MarioBlock.png");
	Renderer->SetTransform({ {0,400 }, { 1024,1024 } });
	AnimationAuto(Renderer, "Idle", 0, 3, 0.2f);
	SetAnimation("Idle");

	ColRenderer = CreateImageRenderer(MarioRenderOrder::Block);
	ColRenderer->SetImage("BlockCollision.png");
	ColRenderer->SetTransform({ {0, 368 }, { 128,128 } });
	ColRenderer->SetActive(false);

	BodyCollision = CreateCollision(MarioCollisionOrder::Block);
	BodyCollision->SetTransform({ { 0, 368 }, { 64, 64} });


}

void MarioBlock::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	BoxCollisionEvent(State);

}

void MarioBlock::StateUpdate(float _DeltaTime)
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

void MarioBlock::SetBoxState(BlockState _MarioBlockState)
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

void MarioBlock::BoxCollisionEvent(BlockState _MarioBlockState)
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

void MarioBlock::ItemStart()
{

}

void MarioBlock::NoneStart()
{

	//SetAnimation("");
}

