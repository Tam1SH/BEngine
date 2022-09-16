
#include "platform.hpp"
#include <boost/filesystem.hpp>
#include <variant>

export module GameObjectFactory;
import Light;
import Camera;
import CRender;
import RenderDecl;
import RenderAllocatorDecl;
import RenderObjectFactoryDecl;
import RenderWorld;
import TransformFactory;
/*Objects*/
import Material;
import DirectionLight;
import GameComponent;
import GameObject;
import Collider;
/*Objects*/

//import VisitorGameComponentDestroyer;
import GameComponentCreateInfo;
import Vector3;

import <memory>;
import <optional>;
import <string>;


using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {
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


		GameObjectFactory(GameObjectFactory&&) noexcept = default;
		GameObjectFactory& operator=(GameObjectFactory&&) noexcept = default;
		GameObjectFactory(const GameObjectFactory& o) = delete;
		GameObjectFactory& operator=(const GameObjectFactory& o) = delete;

		GameObjectFactory(Render& render, RenderAllocator& allocator, Physics& physics, RenderWorld& world) noexcept;

		~GameObjectFactory() noexcept;

	private:
		TransformFactory transFactory;
		//unique_ptr<VisitorGameComponentDestroyer> destroyer;
		RenderObjectFactory renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;

	};

}