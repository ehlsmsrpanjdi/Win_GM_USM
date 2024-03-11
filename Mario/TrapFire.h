#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class TrapFire : public AActor
{
public:
	// constrcuter destructer
	TrapFire();
	~TrapFire();

	// delete Function
	TrapFire(const TrapFire& _Other) = delete;
	TrapFire(TrapFire&& _Other) noexcept = delete;
	TrapFire& operator=(const TrapFire& _Other) = delete;
	TrapFire& operator=(TrapFire&& _Other) noexcept = delete;

protected:
	UCollision* TrapCollision = nullptr;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

