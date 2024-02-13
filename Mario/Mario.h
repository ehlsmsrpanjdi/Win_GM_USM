#pragma once
#include <EngineCore\Actor.h>
#include "MarioHelper.h"
#include "CollisionActor.h"

// Ό³Έν :
class Mario : public CollisionActor
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
	void SetActorCameraPos();
	void StateUpdate(float _DeltaTime) override;
	void AddSpeed(float _DeltaTime, FVector _FVector);
	void SubtractSpeed(float _DeltaTime, FVector _FVector);
	void SetState(MarioState _State);
	bool GravityCheck(float _DeltaTime);


protected:
	void IdleStart();
	void MoveStart();
	void JumpStart();
	void DirChangeStart();
	void NotMoveStart();
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);
	void DirChange(float _DeltaTime);
	void NotMove(float _DeltaTime);
	void MoveFun(float _DeltaTime, FVector Acclerate);
	void CurSpeedDirCheck();
	void ResultMove(float _DeltaTime);

	void SetAnimation(std::string _Name) override;
	std::string GetAnimationName(std::string _Name) override;


	const FVector AccelerateX = { 500.f,0.f,0.f,0.f };
	const FVector AccelerateY = { 0.f,2000.f,0.f,0.f };
	const FVector StopAccelerateX = AccelerateX * 2;
	const FVector DirChangeAccelerateX = StopAccelerateX * 2;
	const FVector StopSpeed = { 0,0,0,0 };
	FVector CurSpeed = { 0,0,0,0 };

	bool DirChanging = false;

	const float MinSpeed = 5.f;
	const float MaxSpeedX = 500.f;
	const float  MaxSpeedY = 1000.f;
	int CurSpeedDir = 0;
	const float JumpPower = -2000.f;
	bool Jumping = false;

private:
	UImageRenderer* Renderer = nullptr;
	MarioState State = MarioState::None;
};

