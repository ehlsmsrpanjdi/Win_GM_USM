#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore\EngineResourcesManager.h>
#include "MarioHelper.h"


// Ό³Έν :
class PhysicsActor : public AActor
{
public:
	// constrcuter destructer
	PhysicsActor();
	virtual ~PhysicsActor();

	// delete Function
	PhysicsActor(const PhysicsActor& _Other) = delete;
	PhysicsActor(PhysicsActor&& _Other) noexcept = delete;
	PhysicsActor& operator=(const PhysicsActor& _Other) = delete;
	PhysicsActor& operator=(PhysicsActor&& _Other) noexcept = delete;

protected:
	void AnimationAuto(UImageRenderer* _Renderer, std::string _Name, int _Start = 0, int _End = 0, float _Time = 0.1f, bool _Routine = true);
	virtual std::string GetAnimationName(std::string _Name);
	virtual void SetAnimation(std::string _Name);

	virtual bool GravityCheck(float _DeltaTime);
	virtual void ResultMove(float _DeltaTime);

	virtual void StateUpdate(float _DeltaTime) {};
	virtual void SetState(MonsterState _State) {};
	virtual void CollisionEvent(MonsterState _MonsterState) {};


	std::string CurAnimationName = "";
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	EActorDir DirState = EActorDir::Right;


	void InteractiveDirCheck();
	void BeginPlay() = 0;
	virtual void Tick(float _DeltaTime) = 0;
	bool NoDir = false;


	FVector CurSpeed = { 0,0,0,0 };
	FVector SpeedX = { 0,0,0,0 };
	FVector SpeedY = { 0,0,0,0 };
	FVector GravitySpeed = { 0,0,0,0 };
	const FVector StopSpeed = { 0,0,0,0 };

private:



};

