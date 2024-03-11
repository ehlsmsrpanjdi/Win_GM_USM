#pragma once
#include "plant.h"
// Ό³Έν :
class PipePlant : public Plant
{
public:
	// constrcuter destructer
	PipePlant();
	~PipePlant();

	// delete Function
	PipePlant(const PipePlant& _Other) = delete;
	PipePlant(PipePlant&& _Other) noexcept = delete;
	PipePlant& operator=(const PipePlant& _Other) = delete;
	PipePlant& operator=(PipePlant&& _Other) noexcept = delete;

protected:
	void StateUpdate(float _DeltaTime) override;
	bool Start = false;
	bool NoStart = false;
private:

};

