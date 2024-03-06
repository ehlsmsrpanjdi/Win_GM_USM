#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class Pipe : public AActor
{
public:
	// constrcuter destructer
	Pipe();
	~Pipe();

	// delete Function
	Pipe(const Pipe& _Other) = delete;
	Pipe(Pipe&& _Other) noexcept = delete;
	Pipe& operator=(const Pipe& _Other) = delete;
	Pipe& operator=(Pipe&& _Other) noexcept = delete;

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

