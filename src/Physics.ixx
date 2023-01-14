export module Physics;
import Vector3;
import Collider;
import RigidBody;
import <optional>;

namespace BEbraEngine {

    //Меня безумно доебало уже бороться с ёбнутыми потугами компилятора. По этому и навтыкал void
	export struct Physics {

        virtual std::optional<Collider*> getObjectRayCast(const Vector3& start, Vector3& end) = 0;

        virtual void update() = 0;

        virtual void addRigidBody(RigidBody& body) = 0;

        virtual void removeRigidBody(RigidBody& body) = 0;

        virtual void removeCollider(Collider& col) = 0;

        virtual void debugDraw() = 0;

        virtual void setCollder(RigidBody& body, Collider& collider) = 0;
	};
}