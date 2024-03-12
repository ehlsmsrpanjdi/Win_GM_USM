#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"
// Ό³Έν :
class ItemBase : public PhysicsActor
{
public:
	// constrcuter destructer
	ItemBase();
	~ItemBase();

	// delete Function
	ItemBase(const ItemBase& _Other) = delete;
	ItemBase(ItemBase&& _Other) noexcept = delete;
	ItemBase& operator=(const ItemBase& _Other) = delete;
	ItemBase& operator=(ItemBase&& _Other) noexcept = delete;

protected:

	virtual void Tick(float _DeltaTime) override;

	void Spawn(float _DeltaTime);
	void MushRoom(float _DeltaTime);
	void SpawnScore();

	virtual void IsEdge(float _DeltaTime);
	void ReverseDir();

	virtual void StateUpdate(float _DeltaTime);

	virtual void CollisionEvent();

	ItemState State = ItemState::Spawn;

	float ItemDefaultSpeed = 300.f;
	float SpawnSpeed = -64.f;
	float TotalMove = 0.f;
	bool ScoreSpawn = false;

	bool IsSpawn = false;

private:

};

