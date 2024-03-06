#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class CameraOffCollisionActor : public AActor
{
public:
	// constrcuter destructer
	CameraOffCollisionActor();
	~CameraOffCollisionActor();

	// delete Function
	CameraOffCollisionActor(const CameraOffCollisionActor& _Other) = delete;
	CameraOffCollisionActor(CameraOffCollisionActor&& _Other) noexcept = delete;
	CameraOffCollisionActor& operator=(const CameraOffCollisionActor& _Other) = delete;
	CameraOffCollisionActor& operator=(CameraOffCollisionActor&& _Other) noexcept = delete;

protected:
	UCollision* BanCameraCollision = nullptr;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

