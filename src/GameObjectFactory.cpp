#include "stdafx.h"
#define NOMINMAX
#include "GameObjectFactory.hpp"
#include "TransformFactory.hpp"
#include "IRenderObjectFactory.hpp"
#include "GameObject.hpp"
#include "Physics.hpp"
#include "AbstractRender.hpp"
#include "GameComponentDestroyer.hpp"	
#include "Camera.hpp"
#include "Math.hpp"
namespace BEbraEngine {

	GameObjectFactory::GameObjectFactory(AbstractRender& render, Physics& physics, RenderWorld& world)
	{
		renderFactory = render.getRenderObjectFactory();
		colliderFactory = physics.getColliderFactory();
		rigidBodyFactory = physics.getRigidBodyFactory();
		renderFactory->setWorld(world);
		transFactory = unique_ptr<TransformFactory>(new TransformFactory());
		destroyer = unique_ptr<IVisitorGameComponentDestroyer>(new GameComponentDestroyer(
			*renderFactory, *colliderFactory, *rigidBodyFactory
		));
		renderFactory->setComponentDestroyer(*destroyer);
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

			Collider::CreateInfo cinfo{};
			cinfo.scale = info.transformInfo->scale;
			cinfo.position = info.transformInfo->position;
			opt_collider = colliderFactory->create(cinfo);
			RigidBody::CreateInfo RigidBodyInfo{};
			RigidBodyInfo.position = info.transformInfo->position;
			if (opt_collider.has_value()) {
				RigidBodyInfo.collider = opt_collider.value();
			}

			opt_rigidBody = rigidBodyFactory->create(RigidBodyInfo);
		}

		if (info.renderInfo) 
			opt_renderObj = renderFactory->create(*info.renderInfo);
		else {
			RenderObject::CreateInfo info{};
			opt_renderObj = renderFactory->create(info);
			DEBUG_LOG1("renderInfo doesn't exist in GameObjectCreateInfo");
		}

		if (info.transformInfo)
			opt_transform = transFactory->create(*info.transformInfo);
		else {
			Transform::CreateInfo info{};
			opt_transform = transFactory->create(info);
			DEBUG_LOG1("transformInfo doesn't exist in GameObjectCreateInfo");
		}


		if (info.transformInfo && info.colliderInfo && info.rigidBodyInfo) {
			auto& v = info.transformInfo->position;
			auto& v1 = info.colliderInfo->position;
			auto& v2 = info.rigidBodyInfo->position;

			if (v != v1 || v != v2 || v1 != v2) {
				DEBUG_LOG2("positions are not equal, are they?", 0, "GameComponentCreateInfo", Debug::ObjectType::GameObject, Debug::MessageType::Info);
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
			DEBUG_LOG2("Can't create a object", 0, "Xyu znaet", Debug::ObjectType::GameObject, Debug::MessageType::Error);
			return optional<GameComponent*>();
		}

	}

	shared_ptr<Light> GameObjectFactory::createLight(const Vector3& position)
	{
		Transform::CreateInfo info{};
		info.position = position;
		auto transform = shared_ptr<Transform>(transFactory->create(info).value());
		auto light = shared_ptr<Light>(renderFactory->createLight(Vector3(1), position));
		light->addComponent(transform);

		auto name = light->getName();

		//light->setName(name + std::to_string(workspace->getSize()));
		//workspace->addComponent(light);
		renderFactory->bindTransform(*light, *transform);

		//light->update();
		//render->addLight(light);
		return light;
	}

	shared_ptr<DirectionLight> GameObjectFactory::createDirLight(const Vector3& direction)
	{
		auto light = shared_ptr<DirectionLight>(renderFactory->createDirLight(Vector3(0.1f), direction));

		auto name = light->getName();

		light->update();
		return light;
	}

	void GameObjectFactory::setModel(GameObject& object, const string& path)
	{
		renderFactory->setModel(object.getComponentChecked<RenderObject>(), path);
	}

	void GameObjectFactory::setCollider(Collider& col, Collider::Type type)
	{
		colliderFactory->setShape(col, *colliderFactory->getShape(type).value());
	}

	void GameObjectFactory::setMaterialAsync(shared_ptr<GameObject> object, const Material::CreateInfo& info)
	{
		auto rObj = object->getComponentCheckedPtr<RenderObject>();
		auto mat1 = object->getComponent<Material>();
		if(mat1.has_value())
			mat1.value()->destroy(*destroyer);

		auto opt_mat = renderFactory->createMaterialAsync(rObj,info);
		Material* mat{};
		if (opt_mat.has_value()) {
			mat = opt_mat.value();
		}
		else throw std::exception();
		object->addComponent(shared_ptr<Material>(mat));
	}

	void GameObjectFactory::destroy(GameComponent& object)
	{
		object.destroy(*destroyer);
	}

	void GameObjectFactory::destroy(GameObject& object)
	{
		object.destroy(*destroyer);
	}

	GameObjectFactory::~GameObjectFactory()
	{
	}

	void GameObjectFactory::destroyPointLight(Light& light)
	{
		light.release();
		renderFactory->destroyPointLight(light);
	}



	shared_ptr<SimpleCamera> GameObjectFactory::createCamera(const Vector3& position)
	{
		auto camera = shared_ptr<SimpleCamera>(renderFactory->createCamera(position));
	//	render->addCamera(camera);
	//	render->selectMainCamera(camera.get());
		return camera;
	}
	void GameObjectFactory::destroyCamera(SimpleCamera& camera)
	{
	}
}