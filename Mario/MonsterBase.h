#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"

// Ό³Έν :
class MonsterBase : public PhysicsActor
{
public:
	// constrcuter destructer
	MonsterBase();
	~MonsterBase();

	// delete Function
	MonsterBase(const MonsterBase& _Other) = delete;
	MonsterBase(MonsterBase&& _Other) noexcept = delete;
	MonsterBase& operator=(const MonsterBase& _Other) = delete;
	MonsterBase& operator=(MonsterBase&& _Other) noexcept = delete;

	virtual void SetMonsterState(MonsterState _State);
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;
	virtual void IsEdge(float _DeltaTime);
	void ReverseDir();

	virtual void StateUpdate(float _DeltaTime) override;
	
	virtual void CollisionEvent(float _DeltaTime);


	void InteractiveDirCheck();


	void Idle(float _DeltaTime);
	void Crouch(float _DeltaTime);
	void CrouchMove(float _DeltaTime);
	void Dead(float _DeltaTime);
	virtual void Excute(float _DeltaTime);

	void IdleStart();
	void CrouchStart();
	void CrouchMoveStart();
	void DeadStart();
	void ExcuteStart();


	MonsterState State = MonsterState::None;

	float MonsterDefaultSpeed = 200.f;
	float CrouchDefaultMoveSpeed = 600.f;

	bool IsInit = false;
	bool ScoreSpawn = false;
	virtual void MonsterInit();

private:

};

