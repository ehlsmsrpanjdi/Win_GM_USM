#pragma once
#include "PhysicsActor.h"
#include <EnginePlatform/EngineSound.h>
// Ό³Έν :
class Flat : public PhysicsActor
{
public:
	// constrcuter destructer
	Flat();
	~Flat();

	// delete Function
	Flat(const Flat& _Other) = delete;
	Flat(Flat&& _Other) noexcept = delete;
	Flat& operator=(const Flat& _Other) = delete;
	Flat& operator=(Flat&& _Other) noexcept = delete;

protected:
	UImageRenderer* FloatRenderer[13] = { nullptr, };
	UImageRenderer* AxeRenderer = nullptr;
	UCollision* FloatCollision = nullptr;
	UCollision* AxeCollision = nullptr;
	UEngineSoundPlayer BGMPlayer;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CollisionEvent(float _DeltaTime);
	void FlatDestroy(float _DeltaTime);

	float DestroyTime = 0.1f;
	int FlatCount = 12;

	bool AxeDestroy = false;
private:

};

