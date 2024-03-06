#pragma once
#include "PhysicsActor.h"
// Ό³Έν :
class Coin : public PhysicsActor
{
public:
	// constrcuter destructer
	Coin();
	~Coin();

	// delete Function
	Coin(const Coin& _Other) = delete;
	Coin(Coin&& _Other) noexcept = delete;
	Coin& operator=(const Coin& _Other) = delete;
	Coin& operator=(Coin&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	float UpSpeed = -1000.f;
	float DownSpeed = 3000.f;
	bool ScoreSpawn = false;
private:

};

