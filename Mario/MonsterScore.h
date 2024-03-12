#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class MonsterScore : public AActor
{
public:
	// constrcuter destructer
	MonsterScore();
	~MonsterScore();

	// delete Function
	MonsterScore(const MonsterScore& _Other) = delete;
	MonsterScore(MonsterScore&& _Other) noexcept = delete;
	MonsterScore& operator=(const MonsterScore& _Other) = delete;
	MonsterScore& operator=(MonsterScore&& _Other) noexcept = delete;

protected:
	UImageRenderer* ScoreRenderer[5] = { nullptr, };

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

