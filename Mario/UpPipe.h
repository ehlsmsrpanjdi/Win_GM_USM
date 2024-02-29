#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class UpPipe : public AActor
{
public:
	// constrcuter destructer
	UpPipe();
	~UpPipe();

	// delete Function
	UpPipe(const UpPipe& _Other) = delete;
	UpPipe(UpPipe&& _Other) noexcept = delete;
	UpPipe& operator=(const UpPipe& _Other) = delete;
	UpPipe& operator=(UpPipe&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	UCollision* BodyCollision = nullptr;
	UImageRenderer* BodyRenderer = nullptr;
	bool EndUp = false;
	bool NotCollision = true;
	float TotalMove = 0.f;
private:

};

