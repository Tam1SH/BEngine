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
		friend class Physics;

		struct CreateInfo {
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

		void moveTo(const Vector3& point) noexcept;

		void lockRotateX(bool yesno);

		void lockRotateY(bool yesno);

		void lockRotateZ(bool yesno);

		void setMaxVelocity(float velocity);

		float getMaxVelocity();

		/// <summary>  
		/// Обнуляются сила и гравитация и объект перемещается в позицию, полученную из привязанного transform
		///</summary>
		void resetState() noexcept;

		btRigidBody& getRigidBody() const noexcept { return *body; }

		/// <summary>  
		/// Устанавливается указатель на новый transform. Предыдущий должен быть переиспользован либо удалён.
		/// </summary>
		void setTransform(TransformSetInfo& transform) noexcept;

		void setMass(float mass) noexcept;

		Vector3 getVelocity() noexcept;

		Vector3 getDirection() noexcept;

		/// <summary>  
		/// Обнуляется линейный и угловой фактор(Factor)
		/// </summary>
		void setDynamic(bool isActive) noexcept;

		bool getDynamic() const noexcept { return isActive; }

		/// <summary>  
		///  Устанавливается в выбранную позицию, обновляется привязанный tranform и обнуляется состояние объекта.
		/// </summary>
		void setPosition(const Vector3& position) noexcept;

		void setRotation(const Quaternion& quat) noexcept;

		void applyExplosionImpulse(float force, float radius, const Vector3& point) noexcept;

		void applyImpulse(const Vector3& force, const Vector3& direction) noexcept;

		void applyImpulseToPoint(float force, const Vector3& point) noexcept;

		Transform& getTransform() const noexcept { return *transform; }

		~RigidBody() noexcept;

	private:

		RigidBody() noexcept;

		unique_ptr<btRigidBody> body;

		float maxVelocity { 200 };

		Collider* collider{};

		Transform* transform{};

		btVector3 linearFactor{};

		btVector3 AngularFactor{};

		bool isActive = true;
	

	};
}

