#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"

class Koopa;
// ���� :
class KoopaFire : public PhysicsActor
{
public:
	// constrcuter destructer
	KoopaFire();
	~KoopaFire();

	friend Koopa;

	// delete Function
	KoopaFire(const KoopaFire& _Other) = delete;
	KoopaFire(KoopaFire&& _Other) noexcept = delete;
	KoopaFire& operator=(const KoopaFire& _Other) = delete;
	KoopaFire& operator=(KoopaFire&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CollisionEvent(float _DeltaTime);
private:

};
