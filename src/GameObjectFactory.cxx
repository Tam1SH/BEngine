module GameObjectFactory;
import RenderAllocator;
import RenderWorld;
import Render;
import GameComponentCreateInfo;
import TransformFactory;
import ColliderFactory;
import RigidBodyFactory;
import GameComponentDestroyer;
import RenderObjectFactory;
import MeshFactory;
import <variant>;
import <memory>;
import <optional>;
import <string>;

using std::optional;
using std::shared_ptr;
using std::string;
using std::unique_ptr;

namespace BEbraEngine {
	

	GameObjectFactory::GameObjectFactory(TransformFactory& transFactory, GameComponentDestroyer& destroyer,
										RenderObjectFactory& renderFactory, ColliderFactory& colliderFactory, 
										RigidBodyFactory& rigidBodyFactory) noexcept 
	{
		this->transFactory = &transFactory;
		this->destroyer = &destroyer;
		this->renderFactory = &renderFactory;
		this->colliderFactory = &colliderFactory;
		this->rigidBodyFactory = &rigidBodyFactory;
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
			opt_renderObj = renderFactory->create(*info.renderInfo);
		else {
			RenderObjectCreateInfo info{};
			opt_renderObj = renderFactory->create(info);
			//DEBUG_LOG1("renderInfo doesn't exist in GameObjectCreateInfo");
		}

		if (info.transformInfo)
			opt_transform = transFactory->create(*info.transformInfo);
		else {
			Transform::CreateInfo info{};
			opt_transform = transFactory->create(info);
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
			renderFactory->bindTransform(*renderObj, *transform);
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
		if (opt_renderObj.has_value() && 
			opt_transform.has_value()) {

			return optional<GameComponent*>(comp);
		}
		else {
			return optional<GameComponent*>();
		}
		
	}

	optional<shared_ptr<DirectionLight>> GameObjectFactory::createDirLight(const DirectionLightCreateInfo& info)
	{
		return renderFactory->createDirLight(info).and_then([&](auto light_) {
			auto light = shared_ptr<DirectionLight>(light_);
			auto name = light->getName();
			light->update();
			return std::make_optional(light);
		});
	}

	optional<shared_ptr<Light>> GameObjectFactory::createLight(const LightCreateInfo& info)
	{
		return renderFactory->createLight(info).and_then([&](auto light_) {
			Transform::CreateInfo info1{ info.position };
			auto light = shared_ptr<Light>(light_);
			
			transFactory->create(info1).and_then([&](auto transform) {
				light->addComponent(std::make_shared<Transform>(transform));
				renderFactory->bindTransform(*light, *transform);
				light->update();

				return std::make_optional(transform);
			});

			return std::make_optional(light);
		});

	}

	void GameObjectFactory::setMaterialAsync(shared_ptr<GameObject> object, const MaterialCreateInfo& info)
	{
		auto renderObject = object->getComponentCheckedPtr<RenderObject>();
		auto& renderFactory_ = *renderFactory;

		renderFactory_
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
	}


	void GameObjectFactory::setModel(GameObject& object, const string& path)
	{
		renderFactory->setModel(object.getComponentChecked<RenderObject>(), path);
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
		renderFactory->destroyPointLight(light);
	}

	optional<shared_ptr<SimpleCamera>> GameObjectFactory::createCamera(const CameraCreateInfo& info)
	{
		return renderFactory->createCamera(info).and_then([&](auto camera) {
			return std::make_optional(std::make_shared<SimpleCamera>(camera));
		});
	}
	void GameObjectFactory::destroyCamera(SimpleCamera& camera)
	{
	}
	
}