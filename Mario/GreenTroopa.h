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
	void IsEdge(float _DeltaTime);
	void CrouchStart();
	void SetState(MonsterState _State) override;
	void CollisionEvent(MonsterState _MonsterState) override;
	void CrouchMoveStart();
	void CrouchMove(float _DeltaTime);
	void StateUpdate(float _DeltaTime) override;
private:

};

