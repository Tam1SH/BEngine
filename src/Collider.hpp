#pragma once
#include "AbstractComponent.hpp"
#include <Physics/btBulletCollisionCommon.h>
#include "Vector3.hpp"
namespace BEbraEngine {

	class Collider : public GameObjectComponent
	{
	public:
		friend class ColliderFactory;
		enum class Type {
			BOX,
			SPHERE,
			CUSTOM //Åáó?
		};
	public:
		btCollisionObject* get() { return _collider.get(); }

		void setScale(const Vector3& size) {
			this->size = size;
			_collider->getCollisionShape()->setLocalScaling(size);
		}

		Vector3& getSize() {
			return size;
		}
		Vector3 getPosition() {
			return _collider->getWorldTransform().getOrigin();
		}

	private:
		std::unique_ptr<btCollisionObject> _collider;
		Vector3 size;
	};
}

