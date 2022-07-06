#include <memory>
#include <concepts>;

export module ÑVisitorGameComponentDestroyer;

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


	export template<typename T>
		concept CVisitorGameComponentDestroyer = requires(
			/* this */
			T & self,
			/* parameters of interface */
			GameObject & gameObject,
			Light & light,
			DirectionLight & directionLight,
			RenderObject & renderObject,
			RigidBody & rigidBody,
			Collider & collider,
			Texture & texture,
			std::shared_ptr<Texture> shared_ptr_texture,
			Material & material,
			Transform & transform,
			SimpleCamera & simpleCamera
			)
	{
		{ self.destroyGameObject(gameObject) } -> std::same_as<void>;

		{ self.destroyPointLightComponent(light) } -> std::same_as<void>;

		{ self.destroyDirectionLightComponent(directionLight) } -> std::same_as<void>;

		{ self.destroyRenderComponent(renderObject) } -> std::same_as<void>;

		{ self.destroyRigidBodyComponent(rigidBody) } -> std::same_as<void>;

		{ self.destroyColliderComponent(collider) } -> std::same_as<void>;

		{ self.destroyTextureComponent(texture) } -> std::same_as<void>;

		{ self.destroyTextureComponentAsync(shared_ptr_texture) } -> std::same_as<void>;

		{ self.destroyMaterialComponent(material) } -> std::same_as<void>;

		{ self.destroyTransformComponent(transform) } -> std::same_as<void>;

		{ self.destroyCameraComponent(simpleCamera) } -> std::same_as<void>;

	};
}