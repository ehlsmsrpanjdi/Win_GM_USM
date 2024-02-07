#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore\EngineResourcesManager.h>
// Ό³Έν :
class CollisionActor : public AActor
{
public:
	// constrcuter destructer
	CollisionActor();
	~CollisionActor();

	// delete Function
	CollisionActor(const CollisionActor& _Other) = delete;
	CollisionActor(CollisionActor&& _Other) noexcept = delete;
	CollisionActor& operator=(const CollisionActor& _Other) = delete;
	CollisionActor& operator=(CollisionActor&& _Other) noexcept = delete;

	void SetRenderImage(std::string_view _MapImageName);
	void SetColRenderImage(std::string_view _MapImageName);
	void SetCollisionActorImage(std::string_view _MapImageName);

	void SwitchRender();

protected:
private:
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* ColRenderer = nullptr;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
} typedef BackGroundMap;

