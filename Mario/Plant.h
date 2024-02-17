#pragma once
#include "Goomba.h"
// Ό³Έν :
class Plant : public Goomba
{
public:
	// constrcuter destructer
	Plant();
	~Plant();

	// delete Function
	Plant(const Plant& _Other) = delete;
	Plant(Plant&& _Other) noexcept = delete;
	Plant& operator=(const Plant& _Other) = delete;
	Plant& operator=(Plant&& _Other) noexcept = delete;
	FVector StartLocation = {};
	float Time = 1.f;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime) override;
	void CollisionEvent(MonsterState _State);
	void AutoMove(float _DeltaTime, FVector _SpeedX = { 200,0 }) override;
private:

};

