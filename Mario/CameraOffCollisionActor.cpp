#include "CameraOffCollisionActor.h"
#include "MarioHelper.h"

CameraOffCollisionActor::CameraOffCollisionActor() 
{
}

CameraOffCollisionActor::~CameraOffCollisionActor() 
{
}

void CameraOffCollisionActor::BeginPlay()
{
	BanCameraCollision = CreateCollision(MarioCollisionOrder::Object);
	BanCameraCollision->SetTransform({ { 0.f,-160.f }, {64.f,640.f } });
}

void CameraOffCollisionActor::Tick(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (BanCameraCollision->CollisionCheck(MarioCollisionOrder::Player, Result)) {
		MarioHelper::CameraOff = true;
	}

}

