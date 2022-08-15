
#include "platform.hpp"
#include <boost/filesystem.hpp>
export module GameObjectFactory;
import <memory>;
import <optional>;
import <string>;
import Render;
import RenderObjects;
import GameComponent;
import GameObject;
import Camera;
import VisitorGameComponentDestroyer;
import Vector3;
import Collider;

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {
	export class Physics;
	export class GameComponentCreateInfo;
	
	export class TransformFactory;
	export class ColliderFactory;
	export class RigidBodyFactory;
}

namespace BEbraEngine {


	export class GameObjectFactory {
	public:

		optional<GameComponent*> create(const GameComponentCreateInfo& info);

		void destroy(GameComponent& object);

		void destroy(GameObject& object);

		shared_ptr<Light> createLight(const Vector3& position);

		shared_ptr<DirectionLight> createDirLight(const Vector3& direction);

		shared_ptr<SimpleCamera> createCamera(const Vector3& position);

		void setModel(GameObject& object, const string& path);

		void setCollider(Collider& col, ColliderType type);

		void setMaterialAsync(shared_ptr<GameObject> object, const MaterialCreateInfo& info);


		void destroyCamera(SimpleCamera& camera);

		void destroyPointLight(Light& light);

		GameObjectFactory(Render& render, Physics& physics, RenderWorld& world);

		~GameObjectFactory();

	private:
		unique_ptr<TransformFactory> transFactory;
		unique_ptr<VisitorGameComponentDestroyer> destroyer;
		RenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;

	};

}