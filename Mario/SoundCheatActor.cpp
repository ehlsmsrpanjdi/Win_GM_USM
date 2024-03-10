#include "SoundCheatActor.h"
#include "MarioHelper.h"

SoundCheatActor::SoundCheatActor() 
{
}

SoundCheatActor::~SoundCheatActor() 
{
}

void SoundCheatActor::BeginPlay()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Object);
	BodyCollision->SetTransform({ {0,0},{100,100} });
}

void SoundCheatActor::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		MarioHelper::Stage2GroundOut = true;
	}
}

