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

	void AutoMove(float _DeltaTime, FVector _SpeedX = { 200,0 });

	virtual void StateUpdate(float _DeltaTime);
	virtual void SetState(MonsterState _State);
	virtual void CollisionEvent();



	virtual void DeadStart();
	virtual void Idle();
	bool IsDead = false;
	MonsterState State = MonsterState::None;


private:

};

