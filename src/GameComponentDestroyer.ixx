module;
#include <memory>
export module GameComponentDestroyer;
//import ColliderFactory;
import RigidBodyFactoryDecl;
import TextureFactoryDecl;
import RenderObjectFactory;
import Concepts;
import RigidBody;
import GameObject;
import DirectionLight;
import RenderObject;
import Collider;
import Texture;
import Material;
import Transform;
import Camera;
import Light;


using std::shared_ptr;


namespace BEbraEngine {

	export struct GameComponentDestroyer {
		
		void destroyGameObject(GameObject& comp);

		void destroyPointLightComponent(Light& comp);

		void destroyDirectionLightComponent(DirectionLight& comp);

		void destroyTextureComponentAsync(shared_ptr<Texture> comp);

		void destroyRenderComponent(RenderObject& comp);

		void destroyRigidBodyComponent(RigidBody& comp);

		void destroyTransformComponent(Transform& comp);

		void destroyCameraComponent(SimpleCamera& comp);

		void destroyColliderComponent(Collider& comp);

		void destroyMaterialComponent(Material& comp);

		void destroyTextureComponent(Texture& comp);

		GameComponentDestroyer(
			RenderObjectFactory& renderFactory,
			ColliderFactory& colliderFactory,
			RigidBodyFactory& rigidBodyFactory,
			TextureFactory& textureFactory);

		GameComponentDestroyer(const GameComponentDestroyer&) = delete;
		GameComponentDestroyer operator=(const GameComponentDestroyer&) = delete;

		GameComponentDestroyer(GameComponentDestroyer&&) noexcept = default;
		GameComponentDestroyer& operator=(GameComponentDestroyer&&) noexcept = default;


	private:
		RenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;
		TextureFactory* textureFactory;
	};
}
