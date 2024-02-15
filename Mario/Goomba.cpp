#include "Goomba.h"
#include <EngineCore/EngineResourcesManager.h>
#include "MarioHelper.h"
#include "Mario.h"

Goomba::Goomba()
{
}

Goomba::~Goomba()
{
}

void Goomba::BeginPlay()
{
	SetName("Goomba");
	NoDir = true;
	Renderer = CreateImageRenderer(MarioRenderOrder::Monster);
	Renderer->SetImage("Goomba.png");
	Renderer->SetTransform({ {0,0 }, { 128,128 } });
	AnimationAuto(Renderer, "Idle", 0, 1, false, 0.2f);
	SetAnimation("Idle");

	Collision = CreateCollision(MarioCollisionOrder::Monster);
	Collision->SetScale({ 100, 100 });
}

void Goomba::Tick(float _DeltaTime)
{
	AutoMove(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == Collision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Mario* Player = dynamic_cast<Mario*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("터져야겠지....");
		}

		Destroy();
	}

}

void Goomba::DeadStart()
{
}

void Goomba::Idle()
{
}

