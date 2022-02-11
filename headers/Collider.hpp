#pragma once
#include "platform.hpp"
#include "GameComponent.hpp"
#include "Vector3.hpp"
#include "Debug.hpp"

class btCollisionObject;

using BE_STD::unique_ptr;

BE_NAMESPACE_STD_BEGIN

	template<typename T, class D>
	class unique_ptr;

BE_NAMESPACE_STD_END

namespace BEbraEngine {
	
	class Collider final : public GameComponent { DEBUG_DESTROY_CHECK_DECL()
	public:
		friend class ColliderFactory;
		
		struct ColliderCreateInfo 
		{
		public:
			enum class Type {
				Box,
				Sphere,
				Mesh //≈·Û?
			};
		public:
			Vector3 scale{};
			Vector3 position{};
			Type type{};
		};

	public:

		void destroy(IVisitorGameComponentDestroyer& destroyer) override;

		btCollisionObject& get() noexcept { return *_collider; }

		void setScale(const Vector3& size) noexcept;

		Vector3& getSize() noexcept { return size; }

		void setPosition(const Vector3& position) noexcept;

		void setMass(float mass) noexcept;

		Vector3 getPosition() const noexcept;

		Collider() noexcept;

		~Collider() noexcept;

	private:
		unique_ptr<btCollisionObject> _collider;
		Vector3 position;
		Vector3 size;
	};
}

