#include "Door.h"
#include <EngineCore/Collision.h>
#include "MarioHelper.h"

Door::Door() 
{
}

Door::~Door() 
{
}

void Door::BeginPlay()
{

}

void Door::Tick(float _DeltaTime)
{
	UCollision* a = CreateCollision(MarioCollisionOrder::Object);
}

