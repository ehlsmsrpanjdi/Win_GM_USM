#include "Door.h"
#include <EngineCore/Collision.h>
#include "MarioHelper.h"
#include "Mario.h"

Door::Door() 
{
}

Door::~Door() 
{
}

void Door::BeginPlay()
{
	BodyCollision = CreateCollision(MarioCollisionOrder::Object);
	BodyCollision->SetTransform({ { 300,300 } ,{300,300} });
}

void Door::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		Collision->GetOwner()->Destroy();
		MarioHelper::LevelEnd = true;

	}
}

