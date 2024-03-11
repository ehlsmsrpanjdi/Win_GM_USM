#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class SoundCheat : public AActor
{
public:
	// constrcuter destructer
	SoundCheat();
	~SoundCheat();

	// delete Function
	SoundCheat(const SoundCheat& _Other) = delete;
	SoundCheat(SoundCheat&& _Other) noexcept = delete;
	SoundCheat& operator=(const SoundCheat& _Other) = delete;
	SoundCheat& operator=(SoundCheat&& _Other) noexcept = delete;
	void SetBool(bool _Bool);

protected:
	UCollision* CheatCollsion = nullptr;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	bool SoundSet = false;
private:

};

