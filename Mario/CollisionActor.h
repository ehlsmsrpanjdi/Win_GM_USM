#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore\EngineResourcesManager.h>
#include "MarioHelper.h"
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
	void AnimationAuto(UImageRenderer* _Renderer, std::string _Name, int _Start = 0, int _End = 0, bool _DoubleWay = true, float _Time = 0.1f, bool _Routine = true);
	virtual std::string GetAnimationName(std::string _Name);
	virtual void SetAnimation(std::string _Name);

	std::string CurAnimationName = "";
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* ColRenderer = nullptr;
	EActorDir DirState = EActorDir::Right;

	void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;
	bool NoDir = false;

	void AutoMove(float _DeltaTime);


private:



} typedef BackGroundMap;

