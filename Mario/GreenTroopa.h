#pragma once
#include "MonsterBase.h"
// Ό³Έν :
class GreenTroopa : public MonsterBase
{
public:
	// constrcuter destructer
	GreenTroopa();
	~GreenTroopa();

	// delete Function
	GreenTroopa(const GreenTroopa& _Other) = delete;
	GreenTroopa(GreenTroopa&& _Other) noexcept = delete;
	GreenTroopa& operator=(const GreenTroopa& _Other) = delete;
	GreenTroopa& operator=(GreenTroopa&& _Other) noexcept = delete;

	void FlyInit(FVector _StartPos, FVector _EndPos);
protected:
	void BeginPlay() override;
	void CollisionEvent(float _DeltaTime) override;
	void Fly(float _DeltaTime) override;
	void MonsterInit() override;

	FVector StartPos = {};
	FVector EndPos = {};
	float Speed = 200.f;
	FVector CurSpeed = {};
	float MaxSpeed = 200.f;
private:

};

