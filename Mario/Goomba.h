#pragma once
#include "CollisionActor.h"
// Ό³Έν :
class Goomba : public CollisionActor
{
public:
	// constrcuter destructer
	Goomba();
	~Goomba();

	// delete Function
	Goomba(const Goomba& _Other) = delete;
	Goomba(Goomba&& _Other) noexcept = delete;
	Goomba& operator=(const Goomba& _Other) = delete;
	Goomba& operator=(Goomba&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void AutoMove(float _DeltaTime, FVector _SpeedX = { 200,0 });



	virtual void StateUpdate(float _DeltaTime);
	virtual void SetState(MonsterState _State);
	virtual void CollisionEvent(MonsterState _MonsterState);



	virtual void DeadStart();
	virtual void Idle(float _DeltaTime);
	virtual void IdleStart();
	MonsterState State = MonsterState::None;

	float AutoMoveSpeed = 200;

private:

};

