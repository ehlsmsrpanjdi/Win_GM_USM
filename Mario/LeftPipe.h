#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class LeftPipe : public AActor
{
public:
	// constrcuter destructer
	LeftPipe();
	~LeftPipe();

	// delete Function
	LeftPipe(const LeftPipe& _Other) = delete;
	LeftPipe(LeftPipe&& _Other) noexcept = delete;
	LeftPipe& operator=(const LeftPipe& _Other) = delete;
	LeftPipe& operator=(LeftPipe&& _Other) noexcept = delete;

	void SetTotalLocation(FVector _PlayerLocation, FVector _CameraLocation);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	UCollision* BodyCollision = nullptr;
	UImageRenderer* BodyRenderer = nullptr;
	float TeleportTime = 1.0f;

	FVector PlayerLocation = {};
	FVector CameraLocation = {};
private:

};

