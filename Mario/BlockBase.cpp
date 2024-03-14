#include "BlockBase.h"
#include "MushRoom.h"
#include "Coin.h"
#include "Mario.h"
#include "ItemFlower.h"
#include "MonsterBase.h"
#include "GroundCoin.h"
#include <EnginePlatform/EngineSound.h>

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
	float CurLocationX = GetActorLocation().X;
	if (MarioHelper::CameraX + MarioHelper::WindowCenter < CurLocationX)
	{
		return;
	}
	else if (!IsInit) {
		IsInit = true;
		BlockInit();
	}

	StateUpdate(_DeltaTime);
	if (CurLocationX < MarioHelper::CameraX - 32) {
		Destroy();
	}
}

void BlockBase::StateUpdate(float _DeltaTime)
{
	switch (BoxState)
	{
	case BlockState::Interactive:
		Interactive(_DeltaTime);
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

void BlockBase::SetItemBlockDefault(int _Count, ItemState _Item, BlockState _BlockState)
{
	SetItemCount(_Count);
	SetItemState(_Item);
	SetBoxState(_BlockState);
}

void BlockBase::SetItemBrickDefault(int _Count, ItemState _Item, BlockState _BlockState)
{
	SetItemCount(_Count);
	SetItemState(_Item);
	SetBoxStartState(_BlockState);
	SetBoxState(_BlockState);
}

void BlockBase::SetBrickDefault()
{
	SetBoxStartState(BlockState::Brick);
	SetBoxState(BlockState::Brick);
	SetItemCount(-1);
}



BlockState BlockBase::GetState()
{
	return BoxState;
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
	if (Interacting == true) {
		return;
	}

	std::vector<UCollision*> MResult;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Item, MResult)) {
		for (UCollision* CoinCollision : MResult) {
			GroundCoin* GCoin = dynamic_cast<GroundCoin*>(CoinCollision->GetOwner());
			if (GCoin == nullptr) {
				continue;
			}
			else {
				Coin* SpawnCoin = GetWorld()->SpawnActor<Coin>(MarioRenderOrder::Item);
				SpawnCoin->SetActorLocation({ GetActorLocation().X, GetActorLocation().Y });
				UEngineSoundPlayer BGMPlayer = UEngineSound::SoundPlay("GainCoin.wav");
				GCoin->Destroy();
			}
		}
	}

	UEngineSoundPlayer BGMPlayer = UEngineSound::SoundPlay("Interactive.wav");
	if (StartState == BlockState::Brick && (MarioHelper::MyMarioClass == MarioClass::Big || MarioHelper::MyMarioClass == MarioClass::Fire)) {
		std::vector<UCollision*> Result;
		if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Monster, Result))
		{
			for (UCollision* Collision : Result) {
				MonsterBase* Monster = (MonsterBase*)Collision->GetOwner();
				Monster->SetMonsterState(MonsterState::Excute);
			}
		}
		UEngineSoundPlayer BGMPlayer = UEngineSound::SoundPlay("BrickBreak.wav");
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
			UEngineSoundPlayer BGMPlayer = UEngineSound::SoundPlay("MushRoomAppear.wav");
			switch (MarioHelper::MyMarioClass)
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
		if (ItemCount == 0 && ItemCount > -1) {
			SetBoxState(BlockState::Default);
		}
		SetBoxState(StartState);
	}
}

void BlockBase::BlockInit()
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
