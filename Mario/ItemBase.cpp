#include "ItemBase.h"
#include "MarioHelper.h"
#include "BlockBase.h"
#include "Mario.h"
#include "MonsterScore.h"

ItemBase::ItemBase()
{
}

ItemBase::~ItemBase()
{
	if (!ScoreSpawn) {
		ScoreSpawn = true;
		MarioHelper::MonsterScore = 0;
		MarioHelper::AddMonsterScore(1000);
		MonsterScore* Score = GetWorld()->SpawnActor<MonsterScore>(MarioRenderOrder::UI);
		Score->SetActorLocation(GetActorLocation());
		MarioHelper::MonsterScore = 0;
		BGMPlayer = UEngineSound::SoundPlay("GainMushRoom.wav");
	}
}


void ItemBase::Tick(float _DeltaTime)
{

	float CameraX = GetWorld()->GetCameraPos().X;
	float WindowCenter = GEngine->MainWindow.GetWindowScale().X;
	float CurLocationX = GetActorLocation().X;

	if (CameraX + WindowCenter < CurLocationX)
	{
		return;
	}

	if (!IsSpawn) {
		Spawn(_DeltaTime);
		return;
	}

	StateUpdate(_DeltaTime);
	CollisionEvent();

	if (CurLocationX < CameraX - 32) {
		Destroy();
	}
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
		float AddPos = SpawnSpeed * _DeltaTime;
		AddActorLocation({ 0.f, AddPos });
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
	FVector CurLocation = GetActorLocation();

	bool IsLeft = MarioHelper::LeftCheck({ CurLocation.X, CurLocation.Y - 6 });
	bool IsRight = MarioHelper::RightCheck({ CurLocation.X, CurLocation.Y - 6 });
	if (IsLeft) {
		ReverseDir();
		return;
	}

	if (IsRight) {
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
		Mario* MyMario = static_cast<Mario*>(Result[0]->GetOwner());

		switch (State)
		{
		case ItemState::MushRoom:
			MyMario->SetMarioClassState(MarioClass::Big);
			Destroy();
			break;
		case ItemState::Flower:
			MyMario->SetMarioClassState(MarioClass::Fire);
			Destroy();
			break;
		case ItemState::Star:
			break;
		default:
			break;
		}
	}

	std::vector<UCollision*> BlockResult;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Block, BlockResult))
	{
		SpeedY.Y = 0;
		GravitySpeed.Y = 0;
		SetActorLocation({ GetActorLocation().X,BlockResult[0]->GetActorBaseTransform().Top() });
		for (UCollision* Collision : BlockResult) {
			BlockBase* Block = (BlockBase*)Collision->GetOwner();
			if (Block->GetState() == BlockState::Interactive) {
				SpeedY.Y = -300.f;
				AddActorLocation(FVector::Up * 5);
				return;
			}
		}
	}
}