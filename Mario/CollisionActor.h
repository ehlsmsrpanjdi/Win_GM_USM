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
	virtual void SetColRenderImage(std::string_view _MapImageName);
	void SetCollisionActorImage(std::string_view _MapImageName);
	void BeginPlay() override;

protected:
private:
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* ColRenderer = nullptr;
} typedef BackGroundMap;

