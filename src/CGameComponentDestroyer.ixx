#include <boost/filesystem.hpp>
export module СGameComponentDestroyer;
import <memory>;
import <concepts>;

//Не имею понятия как можно использовать внутри объявленных классов, т.к forward declatation работает через зад.
namespace BEbraEngine {
	export class RenderObject;
	export class RigidBody;
	export class Texture;
	export class Collider;
	export class Transform;
	export class Light;
	export class DirectionLight;
	export class SimpleCamera;
	export class GameObject;
	export class Material;
}

namespace BEbraEngine {

	export template<typename T>
		concept СGameComponentDestroyer = requires(

			/*void destroyGameObject*/ GameObject & gameObject,

			/*void destroyPointLightComponent*/ Light & light,

			/*void destroyDirectionLightComponent*/ DirectionLight & directionLight,

			/*void destroyRenderComponent*/ RenderObject & renderObject,

			/*void destroyRigidBodyComponent*/ RigidBody & rigidBody,

			/*void destroyColliderComponent*/ Collider & collider,

			/*void destroyTextureComponent*/ Texture & texture,

			/*void destroyTextureComponentAsync*/ std::shared_ptr<Texture> shared_ptr_texture,

			/*void destroyMaterialComponent*/ Material & material,

			/*void destroyTransformComponent*/ Transform & transform,

			/*void destroyCameraComponent*/ SimpleCamera & simpleCamera,

			/* this */
			T & self
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