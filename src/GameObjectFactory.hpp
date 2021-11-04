
#pragma once
#include "AbstractComponent.hpp"
#include "stdafx.h"
#include "AbstractRenderSystem.hpp"
#include "Vector3.hpp"
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


	class GameObjectFactory {

	public:
		GameObjectFactory(std::shared_ptr<AbstractRender> render, std::shared_ptr<Physics> physics);

		std::shared_ptr<GameObject> Create(const Vector3& position);

		std::shared_ptr<Light> createLight(const Vector3& position);

		void Destroy(GameObject* object);

		void Destroy(std::shared_ptr<GameObject> object);

		void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

		~GameObjectFactory();
	private:
		friend class AbstractRender;
		friend class Physics;

		std::shared_ptr<AbstractRender> render;
		std::shared_ptr<Physics> physics;
		std::shared_ptr<WorkSpace> workspace;

		std::unique_ptr<TransformFactory> transFactory;
		std::shared_ptr<IRenderObjectFactory> renderFactory;
	};

}