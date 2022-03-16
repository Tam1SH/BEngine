

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
	class Material;
}

namespace BEbraEngine {

	class IVisitorGameComponentDestroyer {
	public:
		virtual void destroyGameObject(GameObject& comp) = 0;
		virtual void destroyPointLightComponent(Light& comp) = 0;
		virtual void destroyDirectionLightComponent(DirectionLight& comp) = 0;


		virtual void destroyRenderComponent(RenderObject& comp) = 0;
		virtual void destroyRigidBodyComponent(RigidBody& comp) = 0;
		virtual void destroyColliderComponent(Collider& comp) = 0;
		virtual void destroyTextureComponent(Texture& comp) = 0;
		virtual void destroyMaterialComponent(Material& comp) = 0;
		virtual void destroyTransformComponent(Transform& comp) = 0;
		virtual void destroyCameraComponent(SimpleCamera& comp) = 0;

		virtual ~IVisitorGameComponentDestroyer() noexcept {}
		IVisitorGameComponentDestroyer() noexcept {}
	};
}