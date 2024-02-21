#pragma once
#include "Goomba.h"

// Ό³Έν :
class MushRoom : public Goomba
{
public:
	// constrcuter destructer
	MushRoom();
	~MushRoom();

	// delete Function
	MushRoom(const MushRoom& _Other) = delete;
	MushRoom(MushRoom&& _Other) noexcept = delete;
	MushRoom& operator=(const MushRoom& _Other) = delete;
	MushRoom& operator=(MushRoom&& _Other) noexcept = delete;

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Spawn(float _DeltaTime);
	void ItemCollisionEvent();

	float ItemDefaultSpeed = 300.f;
	float SpawnTime = -64.f;
	float TotalMove = 0.f;

private:

};

