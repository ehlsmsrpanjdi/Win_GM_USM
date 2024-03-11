#pragma once
#include "MonsterBase.h"
// Ό³Έν :
class Plant : public MonsterBase
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


protected:
	void BeginPlay() override;
	virtual void StateUpdate(float _DeltaTime) override;
	void CollisionEvent(float _DeltaTime) override;

	UCollision* CheatCollision = nullptr;
	FVector StartLocation = { 0.f,0.f,0.f,0.f };
	FVector NextLocation = {};
	float SpawnTime = 64.f;
	float TotalMove = 0.f;

	int PlantState = 1;

	bool IsUp = false;


private:

};

