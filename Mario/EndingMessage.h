#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class EndingMessage : public AActor
{
public:
	// constrcuter destructer
	EndingMessage();
	~EndingMessage();

	// delete Function
	EndingMessage(const EndingMessage& _Other) = delete;
	EndingMessage(EndingMessage&& _Other) noexcept = delete;
	EndingMessage& operator=(const EndingMessage& _Other) = delete;
	EndingMessage& operator=(EndingMessage&& _Other) noexcept = delete;


protected:
	UImageRenderer* EndingMessageBox = nullptr;
	UImageRenderer* EndingMessageBoxCheat = nullptr;
	UCollision* EndingMessageBoxCollision = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CollisionEvent(float _DeltaTime);

	bool IsEnd = false;
	float NextPageTime = 2.0f;
private:

};

