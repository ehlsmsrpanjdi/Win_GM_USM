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
	void Tick(float _DeltaTime) override;
	void Update(float _DeltaTime);
	//void StateUpdate(float _DeltaTime) override;
	//void CollisionEvent(MonsterState _State);

	FVector StartLocation = { 0.f,0.f,0.f,0.f };
	FVector NextLocation = {};
	float SpawnTime = -64.f;
	float TotalMove = 2.f;

	bool IsUp = true;


private:

};

