

namespace BEbraEngine {
	class RenderObject;
	class RigidBody;
	class Texture;
	class Collider;
	class Transform;
	class Light;
	class DirectionLight;
	class SimpleCamera;
	class GameObject;
}

namespace BEbraEngine {
	class IVisitorGameComponentDestroyer {
	public:
		virtual void destroyGameObject(GameObject& comp) const = 0;
		virtual void destroyPointLightComponent(Light& comp) const = 0;
		virtual void destroyDirectionLightComponent(DirectionLight& comp) const = 0;


		virtual void destroyRenderComponent(RenderObject& comp) const = 0;
		virtual void destroyRigidBodyComponent(RigidBody& comp) const = 0;
		virtual void destroyColliderComponent(Collider& comp) const = 0;
		virtual void destroyMaterialComponent(Texture& comp) const = 0;
		virtual void destroyTransformComponent(Transform& comp) const = 0;
		virtual void destroyCameraComponent(SimpleCamera& comp) const = 0;

		virtual ~IVisitorGameComponentDestroyer() {}
		IVisitorGameComponentDestroyer(){}
	};
}