#pragma once
#include "platform.hpp"
#include "GameComponent.hpp"
#include "Vector3.hpp"
#include "Debug.hpp"
#include "Quaternion.hpp"
class btCollisionObject;



using BE_STD::unique_ptr;

BE_NAMESPACE_STD_BEGIN

	template<typename T, class D>
	class unique_ptr;

BE_NAMESPACE_STD_END

namespace BEbraEngine {
	class RigidBody;
}
namespace BEbraEngine {
	
	class Collider : public GameComponent { DEBUG_DESTROY_CHECK_DECL()
	public:
		friend class ColliderFactory;
		enum class Type {
			Box,
			Sphere,
			Capsule,
			Cylinder,
			Cone,
			Mesh 
		};

		struct ColliderCreateInfo 
		{
		public:
			Vector3 scale{};
			Vector3 position{};
			Type type{};
		};

	public:

		void destroy(IVisitorGameComponentDestroyer& destroyer) override;

		btCollisionObject& get() noexcept { return *_collider; }

		void setScale(const Vector3& size) noexcept;

		void setRotation(const Quaternion& quat) noexcept;

		Vector3& getSize() noexcept { return size; }

		void setPosition(const Vector3& position) noexcept;

		void setMass(float mass) noexcept;

		Vector3 getPosition() const noexcept;

		void setRigidBody(RigidBody& body);

		template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<Collider, T>::value>::type>
		void as() {
			if (dynamic_cast<T*>(this))
				return static_cast<T*>(this);
			else
				throw std::runtime_error("object does not match of type");
		}

		~Collider() noexcept;

	private:

		Collider() noexcept;


		RigidBody* body;
		unique_ptr<btCollisionObject> _collider;
		Vector3 position;
		Vector3 size;
	};
}

