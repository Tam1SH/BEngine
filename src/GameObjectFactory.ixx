module;

#include <variant>
#include <memory>
#include <optional>
#include <string>
#include "Physics.hpp"
export module GameObjectFactory;
import Light;
import Camera;
import RenderObjectFactoryDecl;
import TransformFactory;
import Material;
import DirectionLight;
import GameComponent;
import GameObject;
import Collider;
import GameComponentCreateInfo;
import Vector3;
import GameComponentDestroyerDecl;
import RenderWorld;
import RenderAllocator;
import Render;


using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {
	class Physics;
	export class ColliderFactory;
	export class RigidBodyFactory;
	export class Tranform;
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

		GameObjectFactory(Render& render, RenderAllocator& allocator, Physics& physics, RenderWorld& world) noexcept;

		~GameObjectFactory() noexcept;

		GameObjectFactory(GameObjectFactory&&) noexcept = default;
		GameObjectFactory& operator=(GameObjectFactory&&) noexcept = default;

		GameObjectFactory(const GameObjectFactory& o) = delete;
		GameObjectFactory& operator=(const GameObjectFactory& o) = delete;

	private:
		TransformFactory* transFactory;
		GameComponentDestroyer* destroyer;
		RenderObjectFactory* renderFactory;
		ColliderFactory* colliderFactory;
		RigidBodyFactory* rigidBodyFactory;

	};

}