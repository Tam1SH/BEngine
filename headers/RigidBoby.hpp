#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "GameComponent.hpp"
#include <Physics/btBulletDynamicsCommon.h>
#include "Debug.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
using BE_STD::shared_ptr;
using BE_STD::unique_ptr;
using BE_STD::optional;

namespace BEbraEngine {
	class Transform;
	class Physics;
	class Collider;
}

namespace BEbraEngine {

	class RigidBody : public GameComponent { DEBUG_DESTROY_CHECK_DECL()
	public:
		friend class RigidBodyFactory;

		struct RigidBodyCreateInfo {
			Collider* collider{};
			Vector3 position{};
			float mass{};
		};
		struct TransformSetInfo {
			optional<Transform*> old{};
			Transform* nevv;

		};
	public:

		void destroy(IVisitorGameComponentDestroyer& destroyer) override;

		void resetState() noexcept;

		btRigidBody& getRigidBody() const noexcept { return *body; }

		void setTransform(TransformSetInfo& transform) noexcept;

		void setMass(float mass) noexcept;

		void setDynamic(bool isActive) noexcept;

		bool getDynamic() const noexcept { return isActive; }

		void setPosition(const Vector3& position) noexcept;

		void setRotation(const Quaternion& quat) noexcept;

		void applyImpulse(const Vector3& force, const Vector3& direction) noexcept;

		void applyImpulseToPoint(float force, const Vector3& point) noexcept;

		Transform& getTransform() const noexcept { return *transform; }

		~RigidBody() noexcept;

	private:

		RigidBody() noexcept;

		unique_ptr<btRigidBody> body;

		Collider* collider{};

		Transform* transform{};

		btVector3 linearFactor{};

		btVector3 AngularFactor{};

		bool isActive = true;
	

	};
}

