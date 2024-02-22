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
	virtual void SetState(MonsterState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void IsEdge(float _DeltaTime);
	void ReverseDir();

	virtual void StateUpdate(float _DeltaTime);
	virtual void CollisionEvent(MonsterState _MonsterState);



	virtual void DeadStart();
	virtual void Dead(float _DeltaTime);
	virtual void Excute(float _DeltaTime);
	virtual void ExcuteStart();

	virtual void Idle(float _DeltaTime);
	virtual void IdleStart();
	MonsterState State = MonsterState::None;


	float MonsterDefaultSpeed = 200.f;
	UImageRenderer* ScoreRenderer = nullptr;
	FVector ScoreRendererLocation = FVector::Zero;

private:

};

