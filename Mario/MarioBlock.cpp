#include "MarioBlock.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"
#include "PhysicsActor.h"
#include "MushRoom.h"

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
	Renderer->SetTransform({ {0,0 }, { 1024,1024 } });
	AnimationAuto(Renderer, "Item", 0, 3, 0.2f);
	SetAnimation("Item");

	AnimationAuto(Renderer, "None", 4, 4, 0.1f, false);

	BodyCollision = CreateCollision(MarioCollisionOrder::Block);
	BodyCollision->SetTransform({ { 0, -32 }, { 64, 64} });

	State = BlockState::Item;
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
		Item(_DeltaTime);
		break;
	case BlockState::Brick:
		break;
	case BlockState::None:
		None(_DeltaTime);
		break;
	case BlockState::Break:
		Break(_DeltaTime);
		break;
	case BlockState::Interactive:
		Interactive(_DeltaTime);
		break;
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
		break;
	case BlockState::Interactive:
		InteractiveStart();
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
		switch (State)
		{
		case BlockState::Item:
		{
			if (Mario::PlayerLocation.Y> this->GetActorLocation().Y) {
				SetBoxState(BlockState::Interactive);
			}
		}
		break;
		case BlockState::Brick:
			if (Mario::PlayerLocation.Y> this->GetActorLocation().Y) {
				SetBoxState(BlockState::Interactive);
			}
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
	SetAnimation("None");
}

void MarioBlock::BreakStart()
{
}

void MarioBlock::InteractiveStart()
{
	DeltaTime = 0.1f;
	DefaultLocation = GetActorLocation();
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

void MarioBlock::Interactive(float _DeltaTime)
{
	if (DeltaTime > -0.1f) {
		UpForce += DownForce * _DeltaTime;
		DeltaTime -= _DeltaTime;
		AddActorLocation({ 0.f, UpForce });
	}

	else if(BlockState::Brick == StartState){
		SetActorLocation(DefaultLocation);
		DeltaTime = 0.1f;
		UpForce = -2.f;
		SetBoxState(BlockState::Brick);
	}
	else {
		SetActorLocation(DefaultLocation);
		SetBoxState(BlockState::None);

		MushRoom* TestMushRoom;
		TestMushRoom = this->GetWorld()->SpawnActor<MushRoom>(MarioRenderOrder::Item);
		TestMushRoom->SetActorLocation(this->DefaultLocation);
	}
}

