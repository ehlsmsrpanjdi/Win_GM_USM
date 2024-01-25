#pragma once
#include <EngineCore\Actor.h>

// Ό³Έν :
class Mario : public AActor
{
public:
	// constrcuter destructer
	Mario();
	~Mario();

	// delete Function
	Mario(const Mario& _Other) = delete;
	Mario(Mario&& _Other) noexcept = delete;
	Mario& operator=(const Mario& _Other) = delete;
	Mario& operator=(Mario&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void AddSpeed(FVector _FVector);
	inline void NotMove() {
		CurSpeed.X *= 0.6f;
	}
	FVector AccelerateX = { 500.f,0,0,0 };
	FVector AccelerateY = { 0,500.f,0,0 };
	FVector CurSpeed = { 0,0,0,0 };
	float MaxSpeedX = 500.f;
	float  MaxSpeedY = 500.f;
private:

};

