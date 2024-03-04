#pragma once
#include "PhysicsActor.h"
// Ό³Έν :
class FireWall : public PhysicsActor
{
public:
	// constrcuter destructer
	FireWall();
	~FireWall();

	// delete Function
	FireWall(const FireWall& _Other) = delete;
	FireWall(FireWall&& _Other) noexcept = delete;
	FireWall& operator=(const FireWall& _Other) = delete;
	FireWall& operator=(FireWall&& _Other) noexcept = delete;



protected:
	UImageRenderer* FireWallRenderer[6] = { nullptr, };
	UCollision* FireWallCollision[6] = { nullptr, };
	float Angle = 0.0f;
	float IsRight = 1.0f;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CollisionEvent(float _DeltaTime);
	void SetRight(bool _IsRight);


	void Spin(float _DeltaTime);

private:

};


