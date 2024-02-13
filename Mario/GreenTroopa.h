#pragma once
#include "Goomba.h"
// Ό³Έν :
class GreenTroopa : public Goomba
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
	void Tick(float _DeltaTime) override;
private:

};

