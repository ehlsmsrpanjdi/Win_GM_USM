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


protected:
	void BeginPlay() override;
	void CollisionEvent() override;


private:

};

