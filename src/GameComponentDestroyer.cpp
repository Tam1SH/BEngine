#include "stdafx.h"
#include "GameComponentDestroyer.hpp"
#include "IRenderObjectFactory.hpp"
#include "RenderObject.hpp"
#include "RigidBodyFactory.hpp"
#include "ColliderFactory.hpp"
#include "GameObject.hpp"

namespace BEbraEngine {

	
	GameComponentDestroyer::GameComponentDestroyer(
		IRenderObjectFactory& renderFactory,
		ColliderFactory& colliderFactory,
		RigidBodyFactory& rigidBodyFactory)
	{
		this->renderFactory = &renderFactory;
		this->colliderFactory = &colliderFactory;
		this->rigidBodyFactory = &rigidBodyFactory;
	}

	
	void GameComponentDestroyer::destroyRenderComponent(RenderObject& comp) const
	{
		renderFactory->destroyObject(comp);
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyRigidBodyComponent(RigidBody& comp) const
	{
		rigidBodyFactory->destroy(comp);
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyColliderComponent(Collider& comp) const
	{
		colliderFactory->destroyCollider(comp);
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyMaterialComponent(Texture& comp) const
	{
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyTransformComponent(Transform& comp) const
	{

	}
	void GameComponentDestroyer::destroyPointLightComponent(PointLight& comp) const
	{
		renderFactory->destroyPointLight(comp);

	}
	void GameComponentDestroyer::destroyDirectionLightComponent(DirectionLight& comp) const
	{
		//renderFactory->des

	}
	void GameComponentDestroyer::destroyCameraComponent(SimpleCamera& comp) const
	{
		renderFactory->destroyCamera(comp);
	}

	void GameComponentDestroyer::destroyGameObject(GameObject& comp) const
	{
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	
	
}