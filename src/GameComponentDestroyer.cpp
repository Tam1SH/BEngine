#include "stdafx.h"
#include "GameComponentDestroyer.hpp"
#include "IRenderObjectFactory.hpp"
#include "RenderObject.hpp"
#include "RigidBodyFactory.hpp"
#include "ColliderFactory.hpp"
#include "GameObject.hpp"
#include "ITextureFactory.hpp"

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

	
	void GameComponentDestroyer::destroyRenderComponent(RenderObject& comp)
	{
		renderFactory->destroyObject(comp);
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
		
	}
	void GameComponentDestroyer::destroyRigidBodyComponent(RigidBody& comp)
	{
		rigidBodyFactory->destroy(comp);
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyColliderComponent(Collider& comp)
	{
		colliderFactory->destroyCollider(comp);
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyTextureComponent(Texture& comp)
	{
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
		renderFactory->getTextureFactory().destroyTexture(comp);

	}
	void GameComponentDestroyer::destroyMaterialComponent(Material& comp)
	{
		if (comp.color)
			destroyTextureComponent(*comp.color);
		if (comp.specular)
			destroyTextureComponent(*comp.specular);
		if (comp.normal)
			destroyTextureComponent(*comp.normal);
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyTransformComponent(Transform& comp)
	{

	}
	void GameComponentDestroyer::destroyPointLightComponent(Light& comp)
	{
		renderFactory->destroyPointLight(comp);

	}
	void GameComponentDestroyer::destroyDirectionLightComponent(DirectionLight& comp)
	{
		//renderFactory->des

	}
	void GameComponentDestroyer::destroyCameraComponent(SimpleCamera& comp)
	{
		renderFactory->destroyCamera(comp);
	}

	void GameComponentDestroyer::destroyGameObject(GameObject& comp)
	{
#ifdef _DEBUG
		comp.isDestroyed = true;
#endif // _DEBUG
	}
	
	
}