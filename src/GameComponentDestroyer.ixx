module;
#include <boost/filesystem.hpp>



export module GameComponentDestroyer;
import RenderObject;
import Camera;
import GameObject;
import Light;
import ColliderFactory;
import RigidBodyFactory;
import RenderObjectFactoryDecl;
import Texture;
import Material;
import Collider;
import DirectionLight;
import <memory>;



using std::shared_ptr;


namespace BEbraEngine {

	export class GameComponentDestroyer
	{
	public:
		GameComponentDestroyer(
			RenderObjectFactory& renderFactory,
			ColliderFactory& colliderFactory,
			RigidBodyFactory& rigidBodyFactory);
		
		void destroyGameObject(GameObject& comp);

		void destroyPointLightComponent(Light& comp);

		void destroyDirectionLightComponent(DirectionLight& comp);

		void destroyTextureComponentAsync(shared_ptr<Texture> comp);

		void destroyRenderComponent(RenderObject& comp);

		void destroyRigidBodyComponent(RigidBody& comp);

		void destroyColliderComponent(Collider& comp);
	
		void destroyTextureComponent(Texture& comp);

		void destroyMaterialComponent(Material& comp);

		void destroyTransformComponent(Transform& comp);

		void destroyCameraComponent(SimpleCamera& comp);

	private:
		RenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;


	};

}

module :private;
import ÑGameComponentDestroyer;
namespace BEbraEngine {
	static_assert(ÑGameComponentDestroyer<GameComponentDestroyer>);
}
