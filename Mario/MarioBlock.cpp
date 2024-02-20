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
	AnimationAuto(Renderer, "Item", 0, 3, 0.2f);
	SetAnimation("Item");

	AnimationAuto(Renderer, "None", 4, 4, 0.1f, false);

	BodyCollision = CreateCollision(MarioCollisionOrder::Block);
	BodyCollision->SetTransform({ { 0, 368 }, { 64, 64} });

	State = BlockState::Item;
}

void MarioBlock::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	BoxCollisionEvent(State);

	if (DeltaTime > 0.f) {
		UpForce += DownForce * _DeltaTime;
		DeltaTime -= _DeltaTime;
		AddActorLocation({ 0.f, UpForce  });
	}
}

void MarioBlock::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case BlockState::Item:
		Item(_DeltaTime);
		break;
	case BlockState::Brick:
		break;
	case BlockState::None:
		None(_DeltaTime);
		break;
	case BlockState::Break:
		Break(_DeltaTime);
	default:
		break;
	}
}

void MarioBlock::SetBoxState(BlockState _MarioBlockState)
{
	if (State != _MarioBlockState) {
		State = _MarioBlockState;
	}

	switch (State)
	{
	case BlockState::Item:
		ItemStart();
		break;
	case BlockState::Brick:
		BrickStart();
		break;
	case BlockState::None:
		NoneStart();
		break;
	case BlockState::Break:
		BreakStart();
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

		switch (State)
		{
		case BlockState::Item:
			SetBoxState(BlockState::None);
			break;
		case BlockState::Brick:
			break;
		case BlockState::None:
			break;
		case BlockState::Break:
			break;
		default:
			break;
		}

	}
}

void MarioBlock::ItemStart()
{
	SetAnimation("Item");
}

void MarioBlock::BrickStart()
{
	SetAnimation("Brick");
}

void MarioBlock::NoneStart()
{
	DeltaTime = 0.2f;
	SetAnimation("None");
}

void MarioBlock::BreakStart()
{
}

void MarioBlock::Item(float _DeltaTime)
{
}

void MarioBlock::Brick(float _DeltaTime)
{
}

void MarioBlock::None(float _DeltaTime)
{
}

void MarioBlock::Break(float _DeltaTime)
{
}

