
#pragma once
#include "AbstractComponent.hpp"
#include "stdafx.h"
#include "AbstractRender.hpp"
#include "ColliderFactory.hpp"
#include "RigidBodyFactory.hpp"
#include "Vector3.hpp"
#include "IProxyGameObjectFactory.hpp"
namespace BEbraEngine {
	class GameObject;
	class Physics;
	class Render;
	class TransformFactory;
	class VulkanRenderObjectFactory;
	class RigidBody;
	class WorkSpace;
}

namespace BEbraEngine {


	class GameObjectFactory: public IProxyGameObjectFactory {

	public:
		GameObjectFactory(std::shared_ptr<AbstractRender> render, std::shared_ptr<Physics> physics);

		std::shared_ptr<GameObject> create(const Vector3& position) override;

		std::shared_ptr<PointLight> createLight(const Vector3& position) override;

		std::shared_ptr<DirLight> createDirLight(const Vector3& direction) override;

		void destroyObject(GameObject* object);

		void destroyObject(std::shared_ptr<GameObject> object);

		void destroyPointLight(std::shared_ptr<PointLight> light) override;

		void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

		~GameObjectFactory();
	private:
		friend class Physics;

		std::shared_ptr<AbstractRender> render;
		std::shared_ptr<Physics> physics;
		std::shared_ptr<WorkSpace> workspace;

		std::unique_ptr<TransformFactory> transFactory;
		IRenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;
	};

}