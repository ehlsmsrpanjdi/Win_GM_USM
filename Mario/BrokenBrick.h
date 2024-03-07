#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"
// Ό³Έν :
class BlockBase;
class ULevel;
class BrokenBrick : public PhysicsActor
{
public:
	// constrcuter destructer
	BrokenBrick();
	~BrokenBrick();

	friend BlockBase;
	friend ULevel;

	// delete Function
	BrokenBrick(const BrokenBrick& _Other) = delete;
	BrokenBrick(BrokenBrick&& _Other) noexcept = delete;
	BrokenBrick& operator=(const BrokenBrick& _Other) = delete;
	BrokenBrick& operator=(BrokenBrick&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SetDirState(EActorDir _Dir) {
		DirState = _Dir;
	}

protected:
private:

};

