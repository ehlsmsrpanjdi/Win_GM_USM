#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class Door : public AActor
{
public:
	// constrcuter destructer
	Door();
	~Door();

	// delete Function
	Door(const Door& _Other) = delete;
	Door(Door&& _Other) noexcept = delete;
	Door& operator=(const Door& _Other) = delete;
	Door& operator=(Door&& _Other) noexcept = delete;
	void DoorNextLevel(std::string _NextLevel);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	UCollision* BodyCollision = nullptr;
	std::string NextLevel;
private:

};

