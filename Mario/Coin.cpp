#include "Coin.h"
#include "MarioHelper.h"
#include "MonsterScore.h"
#include <EnginePlatform/EngineSound.h>

Coin::Coin() 
{
	UEngineSoundPlayer BGMPlayer = UEngineSound::SoundPlay("GainCoin.wav");
}

Coin::~Coin() 
{
	if (!ScoreSpawn) {
		ScoreSpawn = true;
		MarioHelper::AddMonsterScore(200);
		MonsterScore* Score = GetWorld()->SpawnActor<MonsterScore>(MarioRenderOrder::UI);
		Score->SetActorLocation(GetActorLocation());
	}
	MarioHelper::MarioCoinCount += 1;
}

void Coin::BeginPlay()
{
	SetName("Coin");
	Renderer = CreateImageRenderer(MarioRenderOrder::Item);
	Renderer->SetImage("Coin.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });
	NoDir = true;
	AnimationAuto(Renderer, "Idle", 0, 3, 0.1f);

	SetAnimation("Idle");

	Destroy(0.5f);

}

void Coin::Tick(float _DeltaTime)
{
	UpSpeed += DownSpeed * _DeltaTime;
	AddActorLocation({0.f,UpSpeed * _DeltaTime});
}

