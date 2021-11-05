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
        object_view->buffer = render->CreateUniformBuffer(sizeof(Matrix4) + sizeof(Vector4));
        object_view->availableRange = sizeof(Matrix4) + sizeof(Vector4);

        auto obj = new VulkanRenderObject();
        obj->name = "RenderObject";
        obj->model = meshFactory->getDefaultModel("BOX");


        obj->texture = std::unique_ptr<Texture>(textureFactory->createEmptyTexture());
        obj->matrix = std::shared_ptr<RenderBufferView>(object_view);
        auto vec = Vector3(0.2, 0.4, 0.3);
        obj->matrix->setData(&vec, sizeof(Vector4), sizeof(Matrix4));
        VulkanDescriptorSetInfo setinfo{};
        setinfo.sampler = obj->texture->sampler;
        setinfo.imageView = obj->texture->imageView;
        setinfo.bufferView = object_view;

        obj->descriptor = render->createDescriptor(&setinfo);
        obj->layout = &render->pipelineLayout;
        return obj;
    }

    Light* VulkanRenderObjectFactory::createLight(const Vector3& color, const Vector3& position)
    {
        auto light = new VulkanLight();
        light->setColor(color);
        
        auto view = new RenderBufferView();
        view->buffer = render->CreateUniformBuffer(sizeof(Vector4) * 2);
        view->availableRange = sizeof(Vector4) * 2;
        auto info = LightDescriptorInfo();
        info.bufferView = view;
        light->data = std::shared_ptr<RenderBufferView>(view);
        light->LightSet = render->createDescriptor(&info);
        light->layout = &render->pipelineLayout;
        return light;
    }

    void VulkanRenderObjectFactory::setContext(std::shared_ptr<AbstractRender> render)
    {
        this->render = std::dynamic_pointer_cast<VulkanRender>(render);
        if (!this->render.get()) {
            Debug::Log("Render turned out not to be suitable.");
        }

        VulkanRenderObject::SetFactory(this);
        textureFactory = new TextureFactory(render.get());

        _pool = std::make_unique<VulkanRenderObjectPool>();
        _pool->setContext(render.get());
        _pool->setFactory(this);
        meshFactory = std::unique_ptr<MeshFactory>(new MeshFactory(render));
        _pool->allocate(10);
    }

    void VulkanRenderObjectFactory::destroyObject(RenderObject* object)
    {
        render->freeDescriptor(static_cast<VulkanRenderObject*>(object)->descriptor);
    }

    void VulkanRenderObjectFactory::BindTransform(Light* light, Transform* transform)
    {
        light->transform = transform;
    }
    void VulkanRenderObjectFactory::BindTransform(RenderObject* object, Transform* transform)
    {
        transform->buffer = object->matrix;
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