module;
#include "Physics.hpp"
export module GameObjectFactory;
import Light;
import Camera;
import TransformFactory;
import Material;
import DirectionLight;
import GameComponent;
import GameObject;
import Collider;
import GameComponentCreateInfo;
import Vector3;
import GameComponentDestroyerDecl;
import RenderObjectFactory;
import RenderWorld;
import RenderAllocator;
import Render;

import <variant>;
import <memory>;
import <optional>;
import <string>;

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;

namespace BEbraEngine {
	export struct ColliderFactory;
	export struct RigidBodyFactory;
	export struct Tranform;
}

namespace BEbraEngine {


	export struct GameObjectFactory {

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