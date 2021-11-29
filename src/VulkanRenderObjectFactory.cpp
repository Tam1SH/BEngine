#include "stdafx.h"
#include "RenderObject.hpp"
#include "VulkanRenderObjectFactory.hpp"
#include "CreateInfoStructures.hpp"
#include "VulkanRender.hpp"
#include "VulkanTextureFactory.hpp"
#include "Image.hpp"
#include "Transform.hpp"
#include "DXRender.hpp"
#include "VkBuffer.hpp"
#include "VulkanObjects.hpp"
#include "Vertex.hpp"
#include "Image.hpp"
#include "VulkanRenderBufferPool.hpp"
#include "Debug.hpp"
#include "MeshFactory.hpp"
#include "Vector2.hpp"

namespace BEbraEngine {

    RenderObject* VulkanRenderObjectFactory::createObject()
    {
        auto maybe_object_view = _poolofObjects->get();
        std::shared_ptr<RenderBufferView> object_view;
        if (maybe_object_view.has_value()) {
            object_view = maybe_object_view.value().lock();
        }
        auto obj = new VulkanRenderObject();
        obj->setName("RenderObject");
        obj->model = meshFactory->getDefaultModel("BOX");

        obj->texture = std::unique_ptr<Texture>(textureFactory->createEmpty());
        obj->matrix = object_view;

        obj->setColor(Vector3(0.2f, 0.4f, 0.3f));
        VulkanDescriptorSetInfo setinfo{};
        setinfo.sampler = obj->texture->sampler;
        setinfo.imageView = obj->texture->imageView;
        setinfo.bufferView = object_view.get();

        obj->descriptor = render->createDescriptor(&setinfo);
        obj->layout = &render->pipelineLayout;
        return obj;
    }

    PointLight* VulkanRenderObjectFactory::createLight(const Vector3& color, const Vector3& position)
    {
        auto maybe_object_view = _poolofPointLights->get();
        std::shared_ptr<RenderBufferView> object_view;
        if (maybe_object_view.has_value()) {
            object_view = maybe_object_view.value().lock();
        }

        auto light = new VulkanPointLight();
        light->setColor(color);
        std::cout << "range: " << object_view->availableRange << std::endl;
        std::cout << "offset: " << object_view->offset << std::endl;
        std::cout << "buffer: " << object_view->buffer << std::endl;
        light->data = object_view;
        light->descriptor = set;

        return light;
    }

    DirectionLight* VulkanRenderObjectFactory::createDirLight(const Vector3& color, const Vector3& direction)
    {
        auto maybe_light_view = _poolofDirLights->get();
        std::shared_ptr<RenderBufferView> view;

        if (maybe_light_view.has_value()) {
            view = maybe_light_view.value().lock();
        }

        auto light = new VulkanDirLight();
        light->setColor(color);
        light->setDirection(direction);


        auto info = LightDescriptorInfo();
        info.bufferView = view.get();
        info.type = LightDescriptorInfo::Type::Direction;

        light->data = view;
        light->descriptor = render->createDescriptor(&info);
        return light;
    }

    void VulkanRenderObjectFactory::setContext(AbstractRender* render)
    {
        this->render = dynamic_cast<VulkanRender*>(render);

        textureFactory = new VulkanTextureFactory(render);
       
        _poolofObjects = std::make_unique<VulkanRenderBufferPool>();
        _poolofObjects->setContext(render);
        _poolofObjects->setUsage(IRenderBufferPool::Usage::SeparateOneBuffer);
        _poolofObjects->allocate(10000, sizeof(RenderObject::ShaderData) * 10000, AbstractRender::TypeBuffer::Storage);
        
        _poolofDirLights = std::make_unique<VulkanRenderBufferPool>();
        _poolofDirLights->setContext(render);
        _poolofDirLights->allocate(1, sizeof(DirectionLight::ShaderData), AbstractRender::TypeBuffer::Storage);

        _poolofPointLights = std::make_unique<VulkanRenderBufferPool>();
        _poolofPointLights->setContext(render);
        _poolofPointLights->setUsage(IRenderBufferPool::Usage::SeparateOneBuffer);
        _poolofPointLights->allocate(100, sizeof(PointLight::ShaderData) * 100, AbstractRender::TypeBuffer::Storage);


        meshFactory = std::unique_ptr<MeshFactory>(new MeshFactory(render));


        auto v =  RenderBufferView();
        v.buffer = _poolofPointLights->getBuffer();
        v.availableRange = sizeof(PointLight::ShaderData) * 100;

        auto info = LightDescriptorInfo();
        info.bufferView = &v;
        info.type = LightDescriptorInfo::Type::Point;
        set = this->render->createDescriptor(&info);
    }

    void VulkanRenderObjectFactory::destroyObject(std::shared_ptr<RenderObject> object)
    {
        auto obj = std::static_pointer_cast<VulkanRenderObject>(object); 
        render->freeDescriptor(obj.get());
        _poolofObjects->free(obj->matrix);
    }

    void VulkanRenderObjectFactory::destroyPointLight(std::shared_ptr<PointLight> light)
    {
        auto light_ = std::static_pointer_cast<VulkanPointLight>(light);
        render->freeDescriptor(light_.get());
        _poolofPointLights->free(light_->data);
    }

    void VulkanRenderObjectFactory::destroyCamera(std::shared_ptr<Camera> camera)
    {
    }

    void VulkanRenderObjectFactory::bindTransform(std::shared_ptr<PointLight> light, std::shared_ptr<Transform> transform)
    {
        light->transform = transform;
    }
    void VulkanRenderObjectFactory::bindTransform(std::shared_ptr<RenderObject> object, std::shared_ptr<Transform> transform)
    {
        object->transform = transform;
    }

    void VulkanRenderObjectFactory::CreateObjectSet(VulkanRenderObject* obj)
    {
        render->freeDescriptor(obj);
        VulkanDescriptorSetInfo setinfo{};
        setinfo.sampler = obj->texture->sampler;
        setinfo.imageView = obj->texture->imageView;
        setinfo.bufferView = obj->matrix.get();
        obj->descriptor = render->createDescriptor(&setinfo);
    }

    VulkanRenderObjectFactory::VulkanRenderObjectFactory()
    {
    }

    VulkanRenderObjectFactory::~VulkanRenderObjectFactory()
    {
    }

    Camera* VulkanRenderObjectFactory::createCamera(const Vector3& position)
    {
        auto camera = new VulkanCamera(Vector2(), position);
        auto view = new RenderBufferView();
        view->availableRange = sizeof(Camera::ShaderData);
        view->buffer = std::shared_ptr<RenderBuffer>(render->createStorageBuffer(sizeof(Camera::ShaderData)));
        camera->cameraData = view;
        camera->descriptor = render->createDescriptor(camera->cameraData->buffer.get());
        return camera;
    }

    void VulkanRenderObjectFactory::setModel(RenderObject* object, const std::string& path)
    {
        object->model.reset();
        auto m =  meshFactory->create(path);
        if (m.has_value()) {
            object->model = std::shared_ptr<Model>(m.value());
        }
    }
}