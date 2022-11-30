
#include "Physics.hpp"
#include <variant>

export module GameObjectFactory_impl;
import GameObjectFactory;
import GameComponentCreateInfo;
import CRender;
import CRenderAllocator;
import CRenderObjectFactory;
import RenderWorld;
import Render;
import CRenderObjectFactory;
import RenderAllocatorDecl;
import TransformFactory;
import ColliderFactory;
import RigidBodyFactory;
import GameComponentDestroyer;
import MeshFactory;
using std::optional;
using std::shared_ptr;
using std::string;
using std::unique_ptr;

namespace BEbraEngine {
	
	GameObjectFactory::GameObjectFactory(Render& render, RenderAllocator& allocator, Physics& physics, RenderWorld& world) noexcept
	{
		
		
		auto meshFactory = MeshFactory(allocator);

		std::visit([&](CRenderAllocator auto& allocator) {
			renderFactory = BEbraEngine::create::renderObjectFactory(render, allocator, std::move(meshFactory));
		}, allocator);

		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			colliderFactory = physics.getColliderFactory();
			rigidBodyFactory = physics.getRigidBodyFactory();
			transFactory = TransformFactory();
			//renderFactory.setComponentDestroyer(*destroyer);
		}, renderFactory);

		destroyer = std::unique_ptr<GameComponentDestroyer>(new GameComponentDestroyer(
			renderFactory, *colliderFactory, *rigidBodyFactory, BEbraEngine::create::textureFactory(render)
		));
		




	}


	optional<GameComponent*> GameObjectFactory::create(const GameComponentCreateInfo& info)
	{
		
		GameComponent* comp;

		optional<Light*> opt_light;
		optional<DirectionLight*> opt_dirLight;
		optional<RenderObject*> opt_renderObj;
		optional<Collider*> opt_collider;
		optional<RigidBody*> opt_rigidBody;
		optional<Transform*> opt_transform;
		optional<Material*> opt_material;

		std::visit([&](CRenderObjectFactory auto& renderFactory) {
		
			if (info.rigidBodyInfo && info.colliderInfo) {

				ColliderCreateInfo cinfo{};
				cinfo.scale = info.transformInfo->scale;
				cinfo.position = info.transformInfo->position;
				opt_collider = colliderFactory->create(cinfo);
				RigidBodyCreateInfo RigidBodyInfo{};
				RigidBodyInfo.position = info.transformInfo->position;
				if (opt_collider.has_value()) {
					RigidBodyInfo.collider = opt_collider.value();
				}

				opt_rigidBody = rigidBodyFactory->create(RigidBodyInfo);
			}

			if (info.renderInfo) 
				opt_renderObj = renderFactory.create(*info.renderInfo);
			else {
				RenderObjectCreateInfo info{};
				opt_renderObj = renderFactory.create(info);
				//DEBUG_LOG1("renderInfo doesn't exist in GameObjectCreateInfo");
			}

			if (info.transformInfo)
				opt_transform = transFactory.create(*info.transformInfo);
			else {
				Transform::CreateInfo info{};
				opt_transform = transFactory.create(info);
				//DEBUG_LOG1("transformInfo doesn't exist in GameObjectCreateInfo");
			}


			if (info.transformInfo && info.colliderInfo && info.rigidBodyInfo) {
				auto& v = info.transformInfo->position;
				auto& v1 = info.colliderInfo->position;
				auto& v2 = info.rigidBodyInfo->position;

				if (v != v1 || v != v2 || v1 != v2) {
					//DEBUG_LOG2("positions are not equal, are they?", 0, "GameComponentCreateInfo", Debug::ObjectType::GameObject, Debug::MessageType::Info);
				}
			}
		
			shared_ptr<RenderObject> renderObj;
			shared_ptr<Transform> transform;
			shared_ptr<Collider> collider;
			shared_ptr<RigidBody> rigidbody;

			comp = new GameObject();


			if (opt_renderObj.has_value()) {
				renderObj = shared_ptr<RenderObject>(opt_renderObj.value());
			
				comp->addComponent(renderObj);
			}


			if (opt_transform.has_value()) {
				transform = shared_ptr<Transform>(opt_transform.value());

				comp->addComponent(transform);
			}

			if (opt_renderObj.has_value() && opt_transform.has_value()) {
				renderFactory.bindTransform(*renderObj, *transform);
			}

			if (info.rigidBodyInfo) {
				collider = shared_ptr<Collider>(opt_collider.value());
				rigidbody = shared_ptr<RigidBody>(opt_rigidBody.value());
				RigidBody::TransformSetInfo info{};
				info.nevv = &*transform;
				rigidbody->setTransform(info);
				collider->setRotation(transform->getRotation());
				comp->addComponent(collider);
				comp->addComponent(rigidbody);
			}
		}, renderFactory);
		if (opt_renderObj.has_value() && 
			opt_transform.has_value()) {

			return optional<GameComponent*>(comp);
		}
		else {
			return optional<GameComponent*>();
		}
		
	}

	shared_ptr<Light> GameObjectFactory::createLight(const Vector3& position)
	{
		
		shared_ptr<Light> light;

		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			Transform::CreateInfo info{};
			info.position = position;
			auto transform = shared_ptr<Transform>(transFactory.create(info).value());
			light = shared_ptr<Light>(renderFactory.createLight(Vector3(1), position));
			light->addComponent(transform);

			auto name = light->getName();

			//light->setName(name + std::to_string(workspace->getSize()));
			//workspace->addComponent(light);

			renderFactory.bindTransform(*light, *transform);

			light->update();
		}, renderFactory);

		//renderAlloc->addLight(light);
		return light;
		
	}

	void GameObjectFactory::setMaterialAsync(shared_ptr<GameObject> object, const MaterialCreateInfo& info)
	{
		auto renderObject = object->getComponentCheckedPtr<RenderObject>();

		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			renderFactory
				.createMaterialAsync(renderObject, info)
				.then([&](std::optional<Material*> material) {
					material
						.and_then([&](Material* material) -> std::optional<Material*> {
							object->addComponent(shared_ptr<Material>(material));
							return std::make_optional(material);
						})
						.or_else([&]() -> std::optional<Material*> { throw std::exception(); });
				})
				.failure([&]() { throw std::exception(); });
		}, renderFactory);
	}


	shared_ptr<DirectionLight> GameObjectFactory::createDirLight(const Vector3& direction)
	{
		
		shared_ptr<DirectionLight> light;
		std::visit([&](CRenderObjectFactory auto& renderFactory) {

			light = shared_ptr<DirectionLight>(renderFactory.createDirLight(Vector3(0.1f), direction));

			auto name = light->getName();

			light->update();

		}, renderFactory);

		return light;
		

	}

	void GameObjectFactory::setModel(GameObject& object, const string& path)
	{
		
		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			renderFactory.setModel(object.getComponentChecked<RenderObject>(), path);
		}, renderFactory);
		
	}

	void GameObjectFactory::setCollider(Collider& col, ColliderType type)
	{
		colliderFactory->setShape(col, *colliderFactory->getShape(type).value());
	}

	void GameObjectFactory::destroy(GameComponent& object)
	{
	}

	void GameObjectFactory::destroy(GameObject& object)
	{
		object.destroy(*destroyer);
	}

	GameObjectFactory::~GameObjectFactory() noexcept
	{
	}

	void GameObjectFactory::destroyPointLight(Light& light)
	{
		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			renderFactory.destroyPointLight(light);
		}, this->renderFactory);

	}



	shared_ptr<SimpleCamera> GameObjectFactory::createCamera(const Vector3& position)
	{
		shared_ptr<SimpleCamera> camera;

		std::visit([&](CRenderObjectFactory auto& renderFactory) {
			camera = shared_ptr<SimpleCamera>(renderFactory.createCamera(position));
			//renderAlloc->addCamera(camera);
			//renderAlloc->selectMainCamera(camera.get());
		}, renderFactory);


		return camera;
	}
	void GameObjectFactory::destroyCamera(SimpleCamera& camera)
	{
	}
	
}