#include "Koopa.h"

Koopa::Koopa()
{
}

Koopa::~Koopa()
{
}

void Koopa::BeginPlay()
{
	MonsterBase::BeginPlay();
	SetName("Koopa");
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("Koopa_Left.png");
	Renderer->SetTransform({ { 0,0 }, { 512,512 } });
	AnimationAuto(Renderer, "Idle", 0, 3, 0.2f);
	SetAnimation("Idle");

	SpeedX.X = -50.f;

}

void Koopa::Tick(float _DeltaTime)
{
	GravityCheck(_DeltaTime);
	ResultMove(_DeltaTime);

	Attack(_DeltaTime);
	Jump(_DeltaTime);
}

void Koopa::Attack(float _DeltaTime)
{
}

void Koopa::Jump(float _DeltaTime)
{
	if (JumpTime > 0) {
		JumpTime -= _DeltaTime;
	}
	else {
		JumpTime = 3.0f;
		SpeedY.Y = -200.f;
	}
}
