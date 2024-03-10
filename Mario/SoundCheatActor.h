#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class SoundCheatActor : public AActor
{
public:
	// constrcuter destructer
	SoundCheatActor();
	~SoundCheatActor();

	// delete Function
	SoundCheatActor(const SoundCheatActor& _Other) = delete;
	SoundCheatActor(SoundCheatActor&& _Other) noexcept = delete;
	SoundCheatActor& operator=(const SoundCheatActor& _Other) = delete;
	SoundCheatActor& operator=(SoundCheatActor&& _Other) noexcept = delete;

protected:
	UCollision* BodyCollision = nullptr;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

