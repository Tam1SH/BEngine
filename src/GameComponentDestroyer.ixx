#include <boost/filesystem.hpp>
export module GameComponentDestroyer;
import VisitorGameComponentDestroyer;
import RenderObjectFactory;
import ColliderFactory;
import RigidBodyFactory;
import <memory>;



using std::shared_ptr;

namespace BEbraEngine {

}
namespace BEbraEngine {


	
	export class GameComponentDestroyer : public VisitorGameComponentDestroyer
	{
	public:
		GameComponentDestroyer(
			RenderObjectFactory& renderFactory,
			ColliderFactory& colliderFactory,
			RigidBodyFactory& rigidBodyFactory);
		
		void destroyGameObject(GameObject& comp) override;

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
