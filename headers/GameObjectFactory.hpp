#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "GameComponentCreateInfo.hpp"
#include "Collider.hpp"

using BE_STD::shared_ptr;
using BE_STD::unique_ptr;
using BE_STD::optional;
using BE_STD::string;

BE_NAMESPACE_STD_BEGIN

	 template<class T> 
	 class shared_ptr;

BE_NAMESPACE_STD_END

namespace BEbraEngine {
	class Physics;
	class Render;
	class TransformFactory;
	class VulkanRenderObjectFactory;
	class RigidBody;
	class WorkSpace;
	class AbstractRender;
	class ColliderFactory;
	class RigidBodyFactory;
	class IRenderObjectFactory;
	class GameComponentCreateInfo;
	class IVisitorGameComponentDestroyer;
	class GameComponent;
	class SimpleCamera;
	class Vector3;
	class GameObject;
	class RenderWorld;
}

namespace BEbraEngine {


	class GameObjectFactory {
	public:

		optional<GameComponent*> create(const GameComponentCreateInfo& info);

		void destroy(GameComponent& object);

		void destroy(GameObject& object);

		shared_ptr<Light> createLight(const Vector3& position);

		shared_ptr<DirectionLight> createDirLight(const Vector3& direction);

		shared_ptr<SimpleCamera> createCamera(const Vector3& position);

		void setModel(GameObject& object, const string& path);

		void setCollider(Collider& col, Collider::Type type);

		void setMaterialAsync(shared_ptr<GameObject> object, const Material::CreateInfo& info);


		void destroyCamera(SimpleCamera& camera);

		void destroyPointLight(Light& light);

		GameObjectFactory(AbstractRender& render, Physics& physics, RenderWorld& world);

		~GameObjectFactory();

	private:
		unique_ptr<TransformFactory> transFactory;
		unique_ptr<IVisitorGameComponentDestroyer> destroyer;
		IRenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;

	};

}