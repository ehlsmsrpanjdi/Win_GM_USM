#include "ItemBase.h"

ItemBase::ItemBase() 
{
}

ItemBase::~ItemBase() 
{
}


void ItemBase::Tick(float _DeltaTime)
{
	if (!IsSpawn) {
		Spawn(_DeltaTime);
		return;
	}
	StateUpdate(_DeltaTime);
	CollisionEvent();
}

void ItemBase::MushRoomStart()
{
}

void ItemBase::FlowerStart()
{
}

void ItemBase::StarStart()
{
}

void ItemBase::Spawn(float _DeltaTime)
{
	if (TotalMove >= -64.f) {
		float AddPos = SpawnSpeed* _DeltaTime;
		AddActorLocation({ 0.f, AddPos});
		TotalMove += AddPos;
	}
	else {
	SetItemState(State);
	IsSpawn = true;
	}
}

void ItemBase::MushRoom(float _DeltaTime)
{
	IsEdge(_DeltaTime);
	SpeedX.X = ItemDefaultSpeed * static_cast<int>(DirState);
	GravityCheck(_DeltaTime);
	ResultMove(_DeltaTime);
}

void ItemBase::Flower(float _DeltaTime)
{
}

void ItemBase::Star(float _DeltaTime)
{
}

void ItemBase::IsEdge(float _DeltaTime)
{
	EActorDir Dir = DirState;

	Color8Bit Color_Right = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX() + 5, GetActorLocation().iY() - 20, Color8Bit::MagentaA);
	Color8Bit Color_Left = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX() - 5, GetActorLocation().iY() - 20, Color8Bit::MagentaA);

	if (Color_Right == Color8Bit(255, 0, 255, 0))
	{
		ReverseDir();
		return;
	}

	if (Color_Left == Color8Bit(255, 0, 255, 0))
	{
		ReverseDir();
		return;
	}
}

void ItemBase::ReverseDir()
{
	if (DirState == EActorDir::Left) {
		DirState = EActorDir::Right;
	}

	else if (DirState == EActorDir::Right) {
		DirState = EActorDir::Left;
	}
}

void ItemBase::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ItemState::MushRoom:
		MushRoom(_DeltaTime);
		break;
	case ItemState::Flower:
		Flower(_DeltaTime);
		break;
	case ItemState::Star:
		Star(_DeltaTime);
		break;
	default:
		break;
	}
}

void ItemBase::SetItemState(ItemState _State)
{
	switch (State)
	{
	case ItemState::MushRoom:
		MushRoomStart();
		break;
	case ItemState::Flower:
		FlowerStart();
		break;
	case ItemState::Star:
		StarStart();
		break;
	default:
		break;
	}
}

void ItemBase::CollisionEvent()
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		Destroy();
	}
}
