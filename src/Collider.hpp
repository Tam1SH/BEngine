#pragma once
#include "GameComponent.hpp"
#include "Vector3.hpp"
#include "Debug.hpp"

class btCollisionObject;

using std::unique_ptr;

namespace std {
	template<typename T, class D>
	class unique_ptr;
}

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

		btCollisionObject& get() { return *_collider; }

		void setScale(const Vector3& size);

		Vector3& getSize() { return size; }

		void setPosition(const Vector3& position);

		void setMass(float mass);

		Vector3 getPosition();

		Collider();

		~Collider();

	private:
		unique_ptr<btCollisionObject> _collider;
		Vector3 size;
	};
}

