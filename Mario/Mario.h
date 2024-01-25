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

	void AddSpeed(FVector _FVector) {

		if (MaxSpeedX >= CurSpeed.X + _FVector.X && -MaxSpeedX <= CurSpeed.X + _FVector.X){
			CurSpeed.X += _FVector.X;
		}

		if (MaxSpeedY >= CurSpeed.Y + _FVector.Y && -MaxSpeedY <= CurSpeed.Y + _FVector.Y) {
			CurSpeed.Y += _FVector.Y;
		}
	}

	FVector AccelerateX = { 500.f,0,0,0 };
	FVector AccelerateY = { 0,500.f,0,0 };
	FVector CurSpeed = { 0,0,0,0 };
	float MaxSpeedX = 100.f;
	float  MaxSpeedY = 100.f;
private:

};

