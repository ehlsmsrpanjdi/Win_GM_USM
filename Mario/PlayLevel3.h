#pragma once
#include <EngineCore\Level.h>


// Ό³Έν :
class PlayLevel3 : public ULevel
{
public:
	// constrcuter destructer
	PlayLevel3();
	~PlayLevel3();

	// delete Function
	PlayLevel3(const PlayLevel3& _Other) = delete;
	PlayLevel3(PlayLevel3&& _Other) noexcept = delete;
	PlayLevel3& operator=(const PlayLevel3& _Other) = delete;
	PlayLevel3& operator=(PlayLevel3&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* Level) override;
private:

};

