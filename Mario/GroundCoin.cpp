#include "GroundCoin.h"
#include "MarioHelper.h"


GroundCoin::GroundCoin() 
{
}

GroundCoin::~GroundCoin() 
{
	MarioHelper::MarioCoinCount++;
	MarioHelper::MarioTotalScore += 100;
}

void GroundCoin::BeginPlay()
{
	SetName("GroundCoin");
	Renderer = CreateImageRenderer(MarioRenderOrder::Item);
	Renderer->SetImage("GroundCoin.png");
	Renderer->SetTransform({ {0,0 }, { 512,512 } });
	NoDir = true;
	AnimationAuto(Renderer, "Idle", 0, 2, 0.2f);

	BodyCollision = CreateCollision(MarioCollisionOrder::Item);
	BodyCollision->SetTransform({ {0,-32 }, { 48,64 } });

	BlockCheakCollision = CreateCollision(MarioCollisionOrder::Item);
	BlockCheakCollision->SetTransform({ {0,-45}, {64,80} });

	SetAnimation("Idle");

}

void GroundCoin::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		Destroy();
	}
}

