#pragma once
#include "MonsterBase.h"

class Flat;
// Ό³Έν :
class Koopa : public MonsterBase
{
public:
	// constrcuter destructer
	Koopa();
	~Koopa();

	friend Flat;
	// delete Function
	Koopa(const Koopa& _Other) = delete;
	Koopa(Koopa&& _Other) noexcept = delete;
	Koopa& operator=(const Koopa& _Other) = delete;
	Koopa& operator=(Koopa&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Attack(float _DeltaTime);
	void CollisionEvent(float _DeltaTime);
	void ExcuteStart() override;
	void Excute(float _DeltaTime) override;
	bool KoopaExcute = false;

	int HP = 5;

	float FireTime = 2.0f;
	float HammerTime = 4.0f;
	float HammerCoolTime = 0.2f;

	void Jump(float _DeltaTime);
	float JumpTime = 3.0f;

	bool KoopaDead(float _DeltaTime);

	void MonsterInit() override;
private:

};

