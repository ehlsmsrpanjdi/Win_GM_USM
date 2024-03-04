#include "Flat.h"
#include "Koopa.h"
#include "Mario.h"


Flat::Flat() 
{
}

Flat::~Flat() 
{
	Koopa::IsKoopaDead = true;
}

void Flat::BeginPlay()
{
	AActor::BeginPlay();
	SetName("Flat");

	FVector RightVector = FVector::Right;

	for (int i = 0; i < 13; ++i) {
		FloatRenderer[i] = CreateImageRenderer(MarioRenderOrder::Cheat);
		FloatRenderer[i]->SetImage("Flat.png");
		FloatRenderer[i]->SetTransform({ { 0 + i * 64,0 }, { 64 , 64 } });
	}

	FloatCollision = CreateCollision(MarioCollisionOrder::Block);
	FloatCollision->SetTransform({ {388,0},{832,64} });

	AxeCollision = CreateCollision(MarioCollisionOrder::Object);
	AxeCollision->SetTransform({ { 832.f,-66.f }, {64.f,196.f } });

	AxeRenderer = CreateImageRenderer(MarioRenderOrder::Map);
	AxeRenderer->SetImage("Axe.png");
	AxeRenderer->SetTransform({ { 800.f,-66.f }, {128.f,196.f } });
}



void Flat::Tick(float _DeltaTime)
{
	CollisionEvent(_DeltaTime);
	FlatDestroy(_DeltaTime);
}

void Flat::CollisionEvent(float _DeltaTime)
{
		std::vector<UCollision*> Result;
		if (true == AxeCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
			Mario* Player = (Mario*)Result[0]->GetOwner();
			AxeDestroy = true;
			AxeRenderer->Destroy();
			AxeCollision->Destroy();
			FloatCollision->Destroy();
			GetWorld()->SetOtherTimeScale(static_cast<int>(MarioRenderOrder::Cheat), 0.0f);
			Player->SetState(MarioState::EndingMove);
		}

		std::vector<UCollision*> MResult;
		if (true == FloatCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
			MarioHelper::IsEndingLevel = true;
		}

}

void Flat::FlatDestroy(float _DeltaTime)
{
	if (!AxeDestroy) {
		return;
	}
	else {
		if (DestroyTime >= 0.f) {
			DestroyTime -= _DeltaTime;
		}
		else if(FlatCount >= 0){
			FloatRenderer[FlatCount]->Destroy();
			--FlatCount;
			DestroyTime = 0.1f;
		}
		else {
			GetWorld()->SetAllTimeScale(1.0f);
			Destroy();
		}
	}
}
