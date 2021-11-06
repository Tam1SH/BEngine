#include "stdafx.h"
#include "RenderObject.hpp"
#include "RenderObjectCreator.hpp"
#include "CreateInfoStructures.hpp"
#include "VulkanRender.hpp"
#include "ImageCreator.hpp"
#include "Image.hpp"
#include "Transform.hpp"
#include "DirectRender.hpp"
#include "VkBuffer.hpp"
#include "RenderBuffer.hpp"
#include "Vertex.hpp"
#include "Image.hpp"
#include "RenderObjectPool.hpp"
#include "Debug.h"
#include "MeshFactory.hpp"
namespace BEbraEngine {

    RenderObject* VulkanRenderObjectFactory::createObject()
    {
        auto object_view = new RenderBufferView();
        object_view->buffer = render->CreateUniformBuffer(sizeof(RenderObject::ShaderData));
        object_view->availableRange = sizeof(RenderObject::ShaderData);

        auto obj = new VulkanRenderObject();
        obj->name = "RenderObject";
        obj->model = meshFactory->getDefaultModel("BOX");

        obj->texture = std::unique_ptr<Texture>(textureFactory->createEmptyTexture());
        obj->matrix = std::shared_ptr<RenderBufferView>(object_view);

        obj->setColor(Vector3(0.2f, 0.4f, 0.3f));
        VulkanDescriptorSetInfo setinfo{};
        setinfo.sampler = obj->texture->sampler;
        setinfo.imageView = obj->texture->imageView;
        setinfo.bufferView = object_view;

        obj->descriptor = render->createDescriptor(&setinfo);
        obj->layout = &render->pipelineLayout;
        return obj;
    }

    PointLight* VulkanRenderObjectFactory::createLight(const Vector3& color, const Vector3& position)
    {
        auto light = new VulkanLight();
        light->setColor(color);
        
        auto view = new RenderBufferView();
        view->buffer = storage;
        view->availableRange = sizeof(PointLight::ShaderData) * 100;
        view->offset = sizeof(PointLight::ShaderData) * current_offset;
        current_offset++;
        auto info = LightDescriptorInfo();
        info.bufferView = view;
        info.type = LightDescriptorInfo::Type::Direction;

        light->data = std::shared_ptr<RenderBufferView>(view);
        light->descriptor = set;
        light->layout = &render->pipelineLayout;

        return light;
    }

    DirLight* VulkanRenderObjectFactory::createDirLight(const Vector3& color, const Vector3& direction)
    {
        auto light = new VulkanDirLight();
        light->setColor(color);
        light->setDirection(direction);

        auto view = new RenderBufferView();
        view->buffer = render->CreateStorageBuffer(sizeof(PointLight::ShaderData));
        view->availableRange = sizeof(PointLight::ShaderData);
        auto info = LightDescriptorInfo();
        info.bufferView = view;
        info.type = LightDescriptorInfo::Type::Direction;

        light->data = std::shared_ptr<RenderBufferView>(view);
        light->descriptor = render->createDescriptor(&info);
        light->layout = &render->pipelineLayout;
        return light;
    }

    void VulkanRenderObjectFactory::setContext(AbstractRender* render)
    {
        this->render = dynamic_cast<VulkanRender*>(render);

        VulkanRenderObject::SetFactory(this);
        textureFactory = new TextureFactory(render);

        _pool = std::make_unique<VulkanRenderObjectPool>();
        _pool->setContext(render);
        _pool->setFactory(this);
        meshFactory = std::unique_ptr<MeshFactory>(new MeshFactory(render));
        _pool->allocate(10);
        storage = this->render->CreateStorageBuffer(sizeof(PointLight::ShaderData) * 100);
        auto view = RenderBufferView();
        view.buffer = storage;
        view.availableRange = sizeof(PointLight::ShaderData) * 100;
        view.offset = 0;
        auto info = LightDescriptorInfo();
        info.bufferView = &view;
        info.type = LightDescriptorInfo::Type::Direction;

        set = this->render->createDescriptor(&info);
    }

    void VulkanRenderObjectFactory::destroyObject(RenderObject* object)
    {
        render->freeDescriptor(static_cast<VulkanRenderObject*>(object));
    }

    void VulkanRenderObjectFactory::BindTransform(PointLight* light, Transform* transform)
    {
        light->transform = transform;
    }
    void VulkanRenderObjectFactory::BindTransform(RenderObject* object, Transform* transform)
    {
        object->transform = transform;
    }

    void VulkanRenderObjectFactory::CreateObjectSet(VulkanRenderObject* obj)
    {
        //render->freeDescriptor(obj->descriptor);
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
}