#pragma once
#include "PhysicsActor.h"
// Ό³Έν :

class AFire;
class AActor;
class FireEnd : public PhysicsActor
{
public:
	// constrcuter destructer
	FireEnd();
	~FireEnd();

	friend AFire;
	friend AActor;

	// delete Function
	FireEnd(const FireEnd& _Other) = delete;
	FireEnd(FireEnd&& _Other) noexcept = delete;
	FireEnd& operator=(const FireEnd& _Other) = delete;
	FireEnd& operator=(FireEnd&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};

