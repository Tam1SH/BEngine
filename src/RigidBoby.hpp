#pragma once
#include "AbstractComponent.hpp"
#include "btBulletDynamicsCommon.h"
#include <memory>
#include <glm/glm.hpp>


namespace BEbraEngine {
	class Transform;
	class Physics;
	class RigidBody : public AbstractComponent
	{
	private:

		friend class Physics;

		static Physics* physics;

		btRigidBody* body;

		btCollisionShape* shape;

		std::shared_ptr<Transform> transform;

		btVector3 linearFactor;

		btVector3 AngularFactor;

		void ResetState();

	public:

		btRigidBody* GetRigidBody() {
			return body;
		}
		static void SetPhysics(Physics* physics);

		void SetTransform(std::shared_ptr<Transform> transform);

		void SetShape(btCollisionShape* newShape);

		void SetDynamic(bool isActive);

		void SetPosition(const glm::vec3& position);

		RigidBody();

		~RigidBody();

	};
}

