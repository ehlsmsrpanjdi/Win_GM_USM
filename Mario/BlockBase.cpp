#include "BlockBase.h"
#include "MushRoom.h"
#include "Coin.h"
#include "Mario.h"
#include "ItemFlower.h"

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
	if (BoxState == BlockState::Default) return;
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

void BlockBase::SetBoxStartState(BlockState _MarioBlockState)
{
	StartState = _MarioBlockState;
}

void BlockBase::BoxCollisionEvent(BlockState _MarioBlockState)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Mario* Player = dynamic_cast<Mario*>(Ptr);

		switch (BoxState)
		{
		case BlockState::ItemBlock:

			break;
		case BlockState::Brick:

			break;
		case BlockState::ItemBrick:

			break;
		default:
			break;
		}


	}
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
	if (StartState == BlockState::Brick && (Mario::MyMarioClass == MarioClass::Big || Mario::MyMarioClass == MarioClass::Fire)) {
		Destroy();
	}
	if (ItemCount >= 1) {
		ItemCount -= 1;
	}

	Interacting = true;
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
	if (ItemCount == 0) {
		SetBoxState(BlockState::Default);
	}
}

void BlockBase::Brick(float _DeltaTime)
{
}

void BlockBase::ItemBrick(float _DeltaTime)
{
	if (ItemCount == 0) {
		SetBoxState(BlockState::Default);
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
		switch (HaveItem)
		{
		case ItemState::MushRoom:
		{
			switch (Mario::MyMarioClass)
			{
			case MarioClass::Small:
			{
				ItemBase* Item;
				Item = GetWorld()->SpawnActor<MushRoom>(MarioRenderOrder::Item);
				Item->SetActorLocation(GetActorLocation());
			}
				break;
			case MarioClass::Big:
			{
				ItemBase* Item;
				Item = GetWorld()->SpawnActor<ItemFlower>(MarioRenderOrder::Item);
				Item->SetActorLocation(GetActorLocation());
				break;
			}
			case MarioClass::Fire:
			{
				ItemBase* Item;
				Item = GetWorld()->SpawnActor<ItemFlower>(MarioRenderOrder::Item);
				Item->SetActorLocation(GetActorLocation());
				break;
			}
			default:
				break;
			}
		}
		break;
		case ItemState::Star:
			break;
		case ItemState::Coin:
		{
			Coin* CoinItem;
			CoinItem = GetWorld()->SpawnActor<Coin>(MarioRenderOrder::Item);
			CoinItem->SetActorLocation(GetActorLocation());
		}
		break;
		default:
			break;
		}
		Interacting = false;
		SetActorLocation(DefaultLocation);
		if (ItemCount <= 0 && ItemCount > -1) {
			SetBoxState(BlockState::Default);
		}
		SetBoxState(StartState);
	}
}

void BlockBase::Default(float _DeltaTime)
{
}

void BlockBase::SetItemCount(int _Count)
{
	ItemCount = _Count;
}

void BlockBase::SetItemState(ItemState _Item)
{
	HaveItem = _Item;
}
