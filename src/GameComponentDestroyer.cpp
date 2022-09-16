#include <boost/filesystem.hpp>

module GameComponentDestroyer;

import <memory>;
using std::shared_ptr;

namespace BEbraEngine {

	GameComponentDestroyer::GameComponentDestroyer(
		RenderObjectFactory& renderFactory,
		ColliderFactory& colliderFactory,
		RigidBodyFactory& rigidBodyFactory)
	{
		this->renderFactory = &renderFactory;
		this->colliderFactory = &colliderFactory;
		this->rigidBodyFactory = &rigidBodyFactory;
	}
	void GameComponentDestroyer::destroyRenderComponent(RenderObject& comp)
	{
		//renderFactory->destroyObject(comp);
#ifdef _DEBUG
		//comp.isDestroyed = true;
#endif // _DEBUG

	}
	void GameComponentDestroyer::destroyRigidBodyComponent(RigidBody& comp)
	{
		rigidBodyFactory->destroy(comp);
#ifdef _DEBUG
		//comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyColliderComponent(Collider& comp)
	{
		colliderFactory->destroyCollider(comp);
#ifdef _DEBUG
		//comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyTextureComponent(Texture& comp)
	{
#ifdef _DEBUG
		//comp.isDestroyed = true;
#endif // _DEBUG
		//renderFactory->getTextureFactory().destroyTextureAsync(comp);

	}
	void GameComponentDestroyer::destroyMaterialComponent(Material& comp)
	{
		if (comp.color)
			destroyTextureComponentAsync(comp.color);
		if (comp.specular)
			destroyTextureComponentAsync(comp.specular);
		if (comp.normal)
			destroyTextureComponentAsync(comp.normal);
#ifdef _DEBUG
		//comp.isDestroyed = true;
#endif // _DEBUG
	}
	void GameComponentDestroyer::destroyTransformComponent(Transform& comp)
	{

	}
	void GameComponentDestroyer::destroyPointLightComponent(Light& comp)
	{
		//renderFactory->destroyPointLight(comp);

	}
	void GameComponentDestroyer::destroyDirectionLightComponent(DirectionLight& comp)
	{
		//renderFactory->des

	}
	void GameComponentDestroyer::destroyCameraComponent(SimpleCamera& comp)
	{
		//renderFactory->destroyCamera(comp);
	}

	void GameComponentDestroyer::destroyTextureComponentAsync(shared_ptr<Texture> comp)
	{

#ifdef _DEBUG
		//comp->isDestroyed = true;
#endif // _DEBUG
		//renderFactory->getTextureFactory().destroyTextureAsync(comp);

	}

	void GameComponentDestroyer::destroyGameObject(GameObject& comp)
	{
#ifdef _DEBUG
		//comp.isDestroyed = true;
#endif // _DEBUG
	}
}