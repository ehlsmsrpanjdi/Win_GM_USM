#pragma once
#include <EngineCore\Actor.h>

// Ό³Έν :
class AFire : public AActor
{
public:
	// constrcuter destructer
	AFire();
	~AFire();

	// delete Function
	AFire(const AFire& _Other) = delete;
	AFire(AFire&& _Other) noexcept = delete;
	AFire& operator=(const AFire& _Other) = delete;
	AFire& operator=(AFire&& _Other) noexcept = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

private:
	FVector Dir = FVector::Zero;
	float Speed = 300.0f;
};

