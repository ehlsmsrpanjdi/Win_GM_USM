#pragma once
#include "MonsterBase.h"


// Ό³Έν :
class Koopa : public MonsterBase
{
public:
	// constrcuter destructer
	Koopa();
	~Koopa();

	// delete Function
	Koopa(const Koopa& _Other) = delete;
	Koopa(Koopa&& _Other) noexcept = delete;
	Koopa& operator=(const Koopa& _Other) = delete;
	Koopa& operator=(Koopa&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	void Attack(float _DeltaTime);
	float FireTime = 2.0f;
	float HammerTime = 4.0f;

	void Jump(float _DeltaTime);
	float JumpTime = 3.0f;
private:

};

