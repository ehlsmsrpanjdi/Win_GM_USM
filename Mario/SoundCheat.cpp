#include "SoundCheat.h"
#include "MarioHelper.h"

SoundCheat::SoundCheat()
{
}

SoundCheat::~SoundCheat()
{
}

void SoundCheat::BeginPlay()
{
	CheatCollsion = CreateCollision(MarioCollisionOrder::Object);
	CheatCollsion->SetTransform({ {0,0}, {64,64} });
}

void SoundCheat::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (CheatCollsion->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		std::string CurLevel = MarioHelper::GetNextLevel();
		if (CurLevel._Equal("Stage1")) {
			MarioHelper::Stage1Sound = SoundSet;
		}
		if (CurLevel._Equal("Stage2")) {
			MarioHelper::Stage2Sound = SoundSet;
		}
	}
}

void SoundCheat::SetBool(bool _Bool)
{
	SoundSet = _Bool;
}

