#include "stdafx.h"
#include "DXRenderObjectFactory.hpp"
#include "DXObjects.hpp"
#include "DXRender.hpp"
namespace BEbraEngine {


   

	void DXRenderObjectFactory::BindTransform(std::shared_ptr<PointLight> light, std::shared_ptr<Transform> transform)
	{
		light->transform = transform;
	}

	void DXRenderObjectFactory::BindTransform(std::shared_ptr<RenderObject> object, std::shared_ptr<Transform> transform)
	{
		object->transform = transform;
	}

	RenderObject* DXRenderObjectFactory::createObject()
	{
		auto maybe_object_view = _poolofObjects->get();
		std::shared_ptr<RenderBufferView> object_view;
		if (maybe_object_view.has_value()) {
			object_view = maybe_object_view.value().lock();
		}
		auto obj = new DXRenderObject();
		obj->SetName("RenderObject");
		obj->model = meshFactory->getDefaultModel("BOX");

		obj->texture = std::unique_ptr<Texture>(textureFactory->createEmpty());
		obj->matrix = object_view;

		obj->setColor(Vector3(0.2f, 0.4f, 0.3f));

		return obj;
	}

	PointLight* DXRenderObjectFactory::createLight(const Vector3& color, const Vector3& position)
	{
		auto maybe_object_view = _poolofPointLights->get();
		std::shared_ptr<RenderBufferView> object_view;
		if (maybe_object_view.has_value()) {
			object_view = maybe_object_view.value().lock();
		}

		auto light = new DXPointLight();
		light->setColor(color);
		return light;
	}

	DirectionLight* DXRenderObjectFactory::createDirLight(const Vector3& color, const Vector3& direction)
	{
		auto maybe_light_view = _poolofDirLights->get();
		std::shared_ptr<RenderBufferView> view;

		if (maybe_light_view.has_value()) {
			view = maybe_light_view.value().lock();
		}

		auto light = new DXDirLight();
		light->setColor(color);
		light->setDirection(direction);

		return light;
	}

	void DXRenderObjectFactory::setContext(AbstractRender* render)
	{
		this->render = dynamic_cast<DXRender*>(render);

		textureFactory = new DXTextureFactory(render);

		_poolofObjects = std::make_unique<RenderBufferPool>();
		_poolofObjects->setContext(render);
		_poolofObjects->setUsage(IRenderBufferPool::Usage::Default);
		_poolofObjects->allocate(500, sizeof(RenderObject::ShaderData), AbstractRender::TypeBuffer::Storage);

		_poolofDirLights = std::make_unique<RenderBufferPool>();
		_poolofDirLights->setContext(render);
		_poolofDirLights->allocate(1, sizeof(DirectionLight::ShaderData), AbstractRender::TypeBuffer::Storage);

		_poolofPointLights = std::make_unique<RenderBufferPool>();
		_poolofPointLights->setContext(render);
		_poolofPointLights->setUsage(IRenderBufferPool::Usage::Default);
		_poolofPointLights->allocate(100, sizeof(PointLight::ShaderData), AbstractRender::TypeBuffer::Storage);


		meshFactory = std::unique_ptr<MeshFactory>(new MeshFactory(render));
	}

	void DXRenderObjectFactory::destroyObject(std::shared_ptr<RenderObject> object)
	{
	}

	void DXRenderObjectFactory::destroyPointLight(std::shared_ptr<PointLight> light)
	{
	}

	void DXRenderObjectFactory::setModel(RenderObject* object, std::string& path)
	{
	}

}