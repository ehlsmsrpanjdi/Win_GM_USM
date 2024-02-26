#include "Fire.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include "BlockBase.h"
#include "MonsterBase.h"
#include "FireEnd.h"

int AFire::FireCount = 0;

AFire::AFire() {

}

AFire::~AFire()
{
	FireEnd* EndFire = GetWorld()->SpawnActor<FireEnd>(MarioRenderOrder::Fire);
	EndFire->SetActorLocation(GetActorLocation());
	--FireCount;
}


void AFire::BeginPlay()
{
	NoDir = true;
	AActor::BeginPlay();
	SetName("Fire");
	Renderer = CreateImageRenderer(MarioRenderOrder::Fire);
	Renderer->SetImage("Fire.png");
	Renderer->SetTransform({ {0,0}, {128, 128} });

	AnimationAuto(Renderer, "Idle", 0, 3);
	Renderer->ChangeAnimation("Idle");
	BodyCollision = CreateCollision(MarioCollisionOrder::Fire);
	BodyCollision->SetColType(ECollisionType::Rect);
	BodyCollision->SetTransform({ { 0,-16 }, { 32, 32 } });
}

void AFire::SetDirState(EActorDir _DirState)
{
	DirState = _DirState;
}

void AFire::Tick(float _DeltaTime)
{
		SpeedX.X = Speed * static_cast<int>(DirState);

		WallCheck(_DeltaTime);
		CollisionEvent(_DeltaTime);

		ResultMove(_DeltaTime);
}

void AFire::CollisionEvent(float _DeltaTime) {
	FVector ThisPosition = this->GetActorLocation();
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Block, Result)) {

		UCollision* Collision = Result[0];
		BlockBase* Block = static_cast<BlockBase*>(Collision->GetOwner());
		FVector BlockVector = Block->GetActorLocation();

		float LeftX = BlockVector.X - 32.f;
		float RightX = BlockVector.X + 32.f;
		float TopY = BlockVector.Y - 62.f;
		float BottomY = BlockVector.Y;

		if (ThisPosition.Y <= TopY) {
			GravitySpeed = FVector::Zero;
			SpeedY.Y = -300.f;
		}

		else if (DirState == EActorDir::Left) {
			if (ThisPosition.X - 16 > RightX)
			{
				Destroy();
			}
		}

		else if (DirState == EActorDir::Right) {
			if (ThisPosition.X + 16 > LeftX)
			{
				Destroy();
			}
		}

	}

	std::vector<UCollision*> MResult;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Monster, MResult)) {
		MonsterBase* Monster = static_cast<MonsterBase*>(MResult[0]->GetOwner());
		Monster->SetMonsterState(MonsterState::Excute);
		Destroy();
	}

}

void AFire::WallCheck(float _DeltaTime)
{
	GravitySpeed += MarioHelper::Gravity * _DeltaTime;

	Color8Bit Color_Bottom = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	Color8Bit Color_Left = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX() - 16, GetActorLocation().iY() - 16, Color8Bit::MagentaA);
	Color8Bit Color_Right = MarioHelper::ColMapImage->GetColor(GetActorLocation().iX() + 16, GetActorLocation().iY() - 16, Color8Bit::MagentaA);


	if (Color_Bottom == Color8Bit(255, 0, 255, 0))
	{
		GravitySpeed = StopSpeed;
		SpeedY.Y = -300.f;
	}

	if (DirState == EActorDir::Left) {
		if (Color_Left == Color8Bit(255, 0, 255, 0))
		{
			Destroy();
		}
	}

	if (DirState == EActorDir::Right) {
		if (Color_Right == Color8Bit(255, 0, 255, 0))
		{
			Destroy();
		}
	}

}
