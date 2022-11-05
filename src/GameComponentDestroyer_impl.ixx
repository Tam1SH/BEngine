#include <boost/filesystem.hpp>
#include <variant>
export module GameComponentDestroyer_impl;
import GameComponentDestroyer;
import CRenderObjectFactory;
import CTextureFactory;
import ColliderFactory;
import RigidBodyFactory;
import <memory>;
import RenderObjectFactoryDecl;
using std::shared_ptr;

namespace BEbraEngine {

	GameComponentDestroyer::GameComponentDestroyer(
		RenderObjectFactory& renderFactory,
		ColliderFactory& colliderFactory,
		RigidBodyFactory& rigidBodyFactory,
		TextureFactory&& textureFactory)
	{
		this->renderFactory = &renderFactory;
		this->colliderFactory = &colliderFactory;
		this->rigidBodyFactory = &rigidBodyFactory;
		this->textureFactory = std::move(textureFactory);
	}

	void GameComponentDestroyer::destroyRenderComponent(RenderObject& comp)
	{
		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			renderFactory.destroyObject(comp);
		}, *renderFactory);
		
	}

	void GameComponentDestroyer::destroyRigidBodyComponent(RigidBody& comp)
	{
		rigidBodyFactory->destroy(comp);
	}

	void GameComponentDestroyer::destroyColliderComponent(Collider& comp)
	{
		colliderFactory->destroyCollider(comp);

	}
	void GameComponentDestroyer::destroyTextureComponent(Texture& comp)
	{
		//std::visit([&](CTextureFactory auto& textureFactory) {
		//	textureFactory.destroyTextureAsync(comp);
		//}, *textureFactory);
	}
	void GameComponentDestroyer::destroyMaterialComponent(Material& comp)
	{
		if (comp.color)
			destroyTextureComponentAsync(comp.color);
		if (comp.specular)
			destroyTextureComponentAsync(comp.specular);
		if (comp.normal)
			destroyTextureComponentAsync(comp.normal);
	}
	void GameComponentDestroyer::destroyTransformComponent(Transform& comp)
	{

	}

	void GameComponentDestroyer::destroyPointLightComponent(Light& comp)
	{
		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			renderFactory.destroyPointLight(comp);
		}, *renderFactory);
	}

	void GameComponentDestroyer::destroyDirectionLightComponent(DirectionLight& comp)
	{

	}
	void GameComponentDestroyer::destroyCameraComponent(SimpleCamera& comp)
	{
		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			renderFactory.destroyCamera(comp);
		}, *renderFactory);
	}

	void GameComponentDestroyer::destroyTextureComponentAsync(shared_ptr<Texture> comp)
	{
		std::visit([&](CTextureFactory auto& textureFactory) {
			textureFactory.destroyTextureAsync(comp);
		}, textureFactory);
		

	}

	void GameComponentDestroyer::destroyGameObject(GameObject& comp)
	{

	}
}