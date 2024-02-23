#include "BlockBase.h"
#include "MushRoom.h"
#include "Coin.h"

BlockBase::BlockBase() 
{
}

BlockBase::~BlockBase() 
{
}

void BlockBase::BeginPlay()
{
}

void BlockBase::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
	BoxCollisionEvent(StartState);
}

void BlockBase::StateUpdate(float _DeltaTime)
{
	switch (BoxState)
	{
	case BlockState::None:
		None(_DeltaTime);
		break;
	case BlockState::ItemBlock:
		ItemBlock(_DeltaTime);
		break;
	case BlockState::Brick:
		Brick(_DeltaTime);
		break;
	case BlockState::ItemBrick:
		ItemBrick(_DeltaTime);
		break;
	case BlockState::Interactive:
		Interactive(_DeltaTime);
		break;
	case BlockState::Default:
		Default(_DeltaTime);
		break;
	default:
		break;
	}
}

void BlockBase::SetBoxState(BlockState _MarioBlockState)
{
	BoxState = _MarioBlockState;

	switch (BoxState)
	{
	case BlockState::None:
		NoneStart();
		break;
	case BlockState::ItemBlock:
		ItemBlockStart();
		break;
	case BlockState::Brick:
		BrickStart();
		break;
	case BlockState::ItemBrick:
		ItemBrickStart();
		break;
	case BlockState::Interactive:
		InteractiveStart();
		break;
	case BlockState::Default:
		DefaultStart();
		break;
	default:
		break;
	}
}

void BlockBase::BoxCollisionEvent(BlockState _MarioBlockState)
{
}

void BlockBase::NoneStart()
{
}

void BlockBase::ItemBlockStart()
{
	SetAnimation("ItemBlock");
}

void BlockBase::BrickStart()
{
	SetAnimation("Brick");
}

void BlockBase::ItemBrickStart()
{
	SetAnimation("Brick");
}

void BlockBase::InteractiveStart()
{
	if (ItemCount >= 1) {
		ItemCount -= 1;
	}
	DeltaTime = 0.1f;
	DefaultLocation = GetActorLocation();
	UpForce = -2.f;

}

void BlockBase::DefaultStart()
{
	SetAnimation("Default");
}

void BlockBase::None(float _DeltaTime)
{
}

void BlockBase::ItemBlock(float _DeltaTime)
{
	if (ItemCount <= 0) {
		SetBoxState(BlockState::None);
	}
}

void BlockBase::Brick(float _DeltaTime)
{
}

void BlockBase::ItemBrick(float _DeltaTime)
{
	if (ItemCount <= 0) {
		SetBoxState(BlockState::None);
	}
}

void BlockBase::Interactive(float _DeltaTime)
{
	if (DeltaTime > -0.1f) {
		UpForce += DownForce * _DeltaTime;
		DeltaTime -= _DeltaTime;
		AddActorLocation({ 0.f, UpForce });
	}
	else {
		SetActorLocation(DefaultLocation);
		SetBoxState(StartState);
	}
	switch (HaveItem)
	{
	case ItemState::MushRoom:
		ItemBase* Item;
		Item = GetWorld()->SpawnActor<MushRoom>(MarioRenderOrder::Item);
		Item->SetActorLocation(GetActorLocation());
		break;
	case ItemState::Flower:
		ItemBase* Item;
		Item = GetWorld()->SpawnActor<MushRoom>(MarioRenderOrder::Item);
		Item->SetActorLocation(GetActorLocation());
		break;
	case ItemState::Star:
		break;
	case ItemState::Coin:
		Coin* CoinItem;
		CoinItem = GetWorld()->SpawnActor<Coin>(MarioRenderOrder::Item);
		CoinItem->SetActorLocation(GetActorLocation());
		break;
	default:
		break;
	}
}

void BlockBase::Default(float _DeltaTime)
{
}
