
#pragma once
#include "AbstractComponent.hpp"
#include "stdafx.h"
#include "AbstractRender.hpp"
#include "ColliderFactory.hpp"
#include "RigidBodyFactory.hpp"
#include "Vector3.hpp"
#include "IProxyGameObjectFactory.hpp"
#include "GameObject.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {
	class Physics;
	class Render;
	class TransformFactory;
	class VulkanRenderObjectFactory;
	class RigidBody;
	class WorkSpace;
}

namespace BEbraEngine {


	class GameObjectFactory : public IProxyGameObjectFactory {

	public:

		optional<shared_ptr<GameObject>> create(const GameObject::GameObjectCreateInfo& info) override;

		shared_ptr<PointLight> createLight(const Vector3& position) override;

		shared_ptr<DirectionLight> createDirLight(const Vector3& direction) override;

		shared_ptr<Camera> createCamera(const Vector3& position) override;

		void setModel(GameObject* object, const std::string& path) override;

		void destroyObject(shared_ptr<GameObject> object) override;

		void destroyCamera(shared_ptr<Camera> camera) override;

		void destroyPointLight(shared_ptr<PointLight> light) override;

		void SetWorkSpace(shared_ptr<WorkSpace> workspace);

		GameObjectFactory(shared_ptr<AbstractRender> render, shared_ptr<Physics> physics);

		~GameObjectFactory();
	private:

		unique_ptr<TransformFactory> transFactory;
		IRenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;

	};

}