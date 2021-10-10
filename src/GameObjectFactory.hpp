#pragma once
#include "AbstractComponent.hpp"

#include <glm/glm.hpp>
#include <memory>
#include "Render.h"

namespace BEbraEngine {
	class GameObject;
	class Physics;
	class Render;
	class TransformFactory;
	class RenderObjectFactory;
	class RigidBody;
	class WorkSpace;

	class GameObjectFactory {
	private:
		friend class Render;
		friend class Physics;

		std::shared_ptr<Render> render;
		std::shared_ptr<Physics> physics;
		std::shared_ptr<WorkSpace> workspace;

		std::unique_ptr<TransformFactory> transFactory;
		std::unique_ptr<RenderObjectFactory> renderFactory;

	public:
		GameObjectFactory(std::shared_ptr<Render> render, std::shared_ptr<Physics> physics);

		std::shared_ptr<GameObject> Create(glm::vec3 position);

		void Destroy(GameObject* object);

		void Destroy(std::shared_ptr<GameObject> object);

		void SetWorkSpace(std::shared_ptr<WorkSpace> workspace);

		~GameObjectFactory();
	};

}