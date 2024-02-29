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

	void SetTotalLocation(FVector _PlayerLocation, FVector _CameraLocation, bool _IsGround);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	UCollision* BodyCollision = nullptr;
	UImageRenderer* BodyRenderer = nullptr;
	float TeleportTime = 2.0f;
	bool IsTeleporting = false;

	FVector PlayerLocation = {};
	FVector CameraLocation = {};
	bool IsGround = false;
private:

};

