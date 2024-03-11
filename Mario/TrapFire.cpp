#include "TrapFire.h"
#include "MarioHelper.h"
#include "KoopaFire.h"

TrapFire::TrapFire() 
{
}

TrapFire::~TrapFire() 
{
}

void TrapFire::BeginPlay()
{
	TrapCollision = CreateCollision(MarioCollisionOrder::Object);
	TrapCollision->SetTransform({ {0,0},{64,600} });
}

void TrapFire::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if(TrapCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		KoopaFire* Fire = GetWorld()->SpawnActor<KoopaFire>(MarioRenderOrder::Monster);
		Fire->SetActorLocation({ GetActorLocation().X + 600,GetActorLocation().Y });
		Fire->SetDir(EActorDir::Left);
		Destroy();
	}
}

