#pragma once
#include <EngineCore\Actor.h>
#include "MarioHelper.h"
#include "PhysicsActor.h"
#include <EngineCore\Collision.h>
#include <EnginePlatform/EngineSound.h>

class MovingBlock;
class ItemBase;
// Ό³Έν :
class Mario : public PhysicsActor
{
public:
	// constrcuter destructer
	Mario();
	~Mario();

	friend MovingBlock;
	friend ItemBase;

	// delete Function
	Mario(const Mario& _Other) = delete;
	Mario(Mario&& _Other) noexcept = delete;
	Mario& operator=(const Mario& _Other) = delete;
	Mario& operator=(Mario&& _Other) noexcept = delete;
	void SetState(MarioState _State);
	void Hit();


	static FVector PlayerLocation;

	void SetAnimation(std::string _Name) override;

	MarioState GetState() {
		return State;
	}

protected:
	void SetMarioClassState(MarioClass _MarioClass);
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SetActorCameraPos();
	void StateUpdate(float _DeltaTime);
	void AddSpeed(float _DeltaTime, FVector _FVector);
	void SubtractSpeed(float _DeltaTime, FVector _FVector);
	void FireAttack(float _DeltaTime);

	UImageRenderer* MushRoomRenderer = nullptr;
	UImageRenderer* FlowerRenderer = nullptr;

protected:
	void IdleStart();
	void MoveStart();
	void JumpStart();
	void DirChangeStart();
	void InteractiveStart();
	void CrouchStart();
	void CrouchJumpStart();
	void DeadStart();
	void EndStart();
	void EndMoveStart();
	void ChangingStart();
	void TelePortingStart();
	void TelePortEndingStart();

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);
	void DirChange(float _DeltaTime);
	void MoveFun(float _DeltaTime, FVector Acclerate);
	void Interactive(float _DeltaTime);
	void Crouch(float _DeltaTime);
	void CrouchJump(float _DeltaTime);
	void Dead(float _DeltaTime);
	void End(float _DeltaTime);
	void EndMove(float _DeltaTime);
	void Changing(float _DeltaTime);
	void EndingMove(float _DeltaTime);
	void Ending(float _DeltaTime);
	void TelePorting(float _DeltaTime);
	void TelePortEnding(float _DeltaTime);

	bool LeftEdgeCheck();
	bool RightEdgeCheck();
	bool TopCheck();
	void DirCheck();

	void MarioFall();

	void MarioCollisionEvent(float _DeltaTime);

	void ResultMove(float _DeltaTime) override;


	FVector AccelerateX = { 400.f,0.f,0.f,0.f };
	const FVector StopAccelerateX = AccelerateX * 2;
	const FVector DirChangeAccelerateX = StopAccelerateX * 2;

	bool Debug = false;
	bool DirChanging = false;
	bool IsCollision = false;

	const float MinSpeed = 10.f;
	float MaxSpeedX = 400.f;
	const float  MaxSpeedY = 1000.f;
	int CurSpeedDir = 0;
	float JumpPower = -900.f;
	bool Jumping = false;
	
	float DeadTime = .5f;

	float EndTime = 0.5f;

	float ChangeTime = 0.6f;
	float GodTime = 0.f;
	float TeleportingTime = 1.f;
	float EndingTime = 16.f;

	float CurFrame = 0;
	float CurFrameTime = 2;
	int CurFrameCount = 0;
	float TotalFrame = 0;
private:
	MarioState State = MarioState::None;
	MarioState PrevState = MarioState::None;

	float ChangeLevelTime = 2.5f;
};

