#pragma once
#include <EngineCore\Actor.h>
#include "MarioHelper.h"
#include "PhysicsActor.h"
#include <EngineCore\Collision.h>

// Ό³Έν :
class Mario : public PhysicsActor
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
	void SetState(MarioState _State);


	static FVector PlayerLocation;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SetActorCameraPos();
	void StateUpdate(float _DeltaTime) override;
	void AddSpeed(float _DeltaTime, FVector _FVector);
	void SubtractSpeed(float _DeltaTime, FVector _FVector);

protected:
	void IdleStart();
	void MoveStart();
	void JumpStart();
	void DirChangeStart();
	void InteractiveStart();
	void DeadStart();
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);
	void DirChange(float _DeltaTime);
	void MoveFun(float _DeltaTime, FVector Acclerate);
	void Interactive(float _DeltaTime);
	void Dead(float _DeltaTime);
	//void EdgeCheck();
	bool LeftEdgeCheck();
	bool RightEdgeCheck();
	void DirCheck();

	void MarioCollisionEvent(float _DeltaTime);

	void ResultMove(float _DeltaTime) override;

	void SetAnimation(std::string _Name) override;

	const FVector AccelerateX = { 500.f,0.f,0.f,0.f };
	const FVector AccelerateY = { 0.f,2000.f,0.f,0.f };
	const FVector StopAccelerateX = AccelerateX * 2;
	const FVector DirChangeAccelerateX = StopAccelerateX * 2;


	bool DirChanging = false;

	const float MinSpeed = 5.f;
	const float MaxSpeedX = 500.f;
	const float  MaxSpeedY = 1000.f;
	int CurSpeedDir = 0;
	const float JumpPower = -1000.f;
	bool Jumping = false;
	
	float DeadTime = .5f;

private:
	MarioState State = MarioState::None;
};

