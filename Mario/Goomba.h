#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"

// Ό³Έν :
class Goomba : public PhysicsActor
{
public:
	// constrcuter destructer
	Goomba();
	virtual ~Goomba();

	// delete Function
	Goomba(const Goomba& _Other) = delete;
	Goomba(Goomba&& _Other) noexcept = delete;
	Goomba& operator=(const Goomba& _Other) = delete;
	Goomba& operator=(Goomba&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void IsEdge(float _DeltaTime);
	void ReverseDir();

	virtual void StateUpdate(float _DeltaTime);
	virtual void SetState(MonsterState _State);
	virtual void CollisionEvent(MonsterState _MonsterState);



	virtual void DeadStart();
	virtual void Idle(float _DeltaTime);
	virtual void IdleStart();
	MonsterState State = MonsterState::None;


	float MonsterDefaultSpeed = 200.f;

private:

};

