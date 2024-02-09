#pragma once
#include <EngineCore\Actor.h>
#include "MarioHelper.h"

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
	void SetActorCameraPos();
	void StateUpdate(float _DeltaTime);
	void AddSpeed(FVector _FVector);
	void SubtractSpeed(FVector _FVector);
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

	std::string GetAnimationName(std::string _Name);
	void SetAnimation(std::string _Name);


	FVector AccelerateX = { 500.f,0.f,0.f,0.f };
	FVector AccelerateY = { 0,500 };
	FVector CurSpeed = { 0,0,0,0 };
	FVector StopSpeed = { 0,0,0,0 };
	float MaxSpeedX = 500.f;
	float  MaxSpeedY = 500.f;
	bool DirChangeing = false;
private:
	UImageRenderer* Renderer = nullptr;
	MarioState State = MarioState::None;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";
};

