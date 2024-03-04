#pragma once
#include <EngineCore/Collision.h>
#include <EngineCore/Actor.h>
// Ό³Έν :
class EndingDoor : public AActor
{
public:
	// constrcuter destructer
	EndingDoor();
	~EndingDoor();

	// delete Function
	EndingDoor(const EndingDoor& _Other) = delete;
	EndingDoor(EndingDoor&& _Other) noexcept = delete;
	EndingDoor& operator=(const EndingDoor& _Other) = delete;
	EndingDoor& operator=(EndingDoor&& _Other) noexcept = delete;

protected:
	UCollision* DoorCollision = nullptr;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:

};

