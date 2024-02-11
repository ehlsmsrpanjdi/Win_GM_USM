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
	void AnimationAuto(UImageRenderer* _Renderer, std::string _Name, int _Start = 0, int _End = 0, float _Time = 0.1f, bool _DoubleWay = true, bool _Routine = true);

	std::string GetAnimationName(std::string _Name);
	void SetAnimation(std::string _Name);


	FVector AccelerateX = { 500.f,0.f,0.f,0.f };
	FVector AccelerateY = { 0.f,500.f,0.f,0.f };
	FVector StopAccelerateX = AccelerateX * 2;
	FVector DirChangeAccelerateX = StopAccelerateX * 2;
	FVector CurSpeed = { 0,0,0,0 };
	FVector StopSpeed = { 0,0,0,0 };
	bool DirChanging = false;
	float MinSpeed = 5.f;
	float MaxSpeedX = 500.f;
	float  MaxSpeedY = 500.f;
	int CurSpeedDir = 0;
private:
	UImageRenderer* Renderer = nullptr;
	MarioState State = MarioState::None;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";
};

