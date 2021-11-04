#include "stdafx.h"
#include "RenderObject.hpp"
#include "RenderObjectCreator.hpp"
#include "CreateInfoStructures.hpp"
#include "VulkanRender.hpp"
#include "ImageCreator.hpp"
#include "Mesh1.hpp"
#include "Image.hpp"
#include "Transform.hpp"
#include "DirectRender.hpp"
#include "VkBuffer.hpp"
#include "RenderBuffer.hpp"
#include "Vertex.hpp"
#include "Image.hpp"
#include "RenderObjectPool.hpp"
#include "Debug.h"
namespace BEbraEngine {

    RenderObject* VulkanRenderObjectFactory::createObject()
    {
        auto object_view = new RenderBufferView();
        object_view->buffer = render->CreateUniformBuffer(sizeof(Matrix4) + sizeof(Vector4));
        object_view->availableRange = sizeof(Matrix4) + sizeof(Vector4);
        auto factory = MeshFactory();

        auto obj = new VulkanRenderObject();
        obj->name = "RenderObject";
       
        obj->model = std::unique_ptr<Model>(factory.create("C:/.BEbraEngine/src/Models/BOX_NAXYU.fbx").value());

        auto vertices_view = new RenderBufferView();
        vertices_view->buffer = render->CreateVertexBuffer(obj->model->meshes[0].vertices);
        obj->model->meshes[0].vertices_view = vertices_view;
        auto indices_view = new RenderBufferView();
        indices_view->buffer = render->CreateIndexBuffer(obj->model->meshes[0].indices);
        obj->model->meshes[0].indices_view = indices_view;


        obj->texture = std::unique_ptr<Texture>(imgsCreator->createEmptyTexture());
        obj->matrix = std::shared_ptr<RenderBufferView>(object_view);
        auto vec = Vector3(0.2, 0.4, 0.3);
        obj->matrix->setData(&vec, sizeof(Vector4), sizeof(Matrix4));
        VulkanDescriptorSetInfo setinfo{};
        setinfo.sampler = obj->texture->sampler;
        setinfo.imageView = obj->texture->imageView;
        setinfo.bufferView = object_view;

        obj->descriptor = render->CreateDescriptor(&setinfo);
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
        auto info = LightInfo();
        info.bufferView = view;
        light->data = std::shared_ptr<RenderBufferView>(view);
        light->LightSet = render->CreateDescriptor(&info);
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
        imgsCreator = new TextureFactory(render.get());

        _pool = std::make_unique<VulkanRenderObjectPool>();
        _pool->setContext(render.get());
        _pool->setFactory(this);

        _pool->allocate(10);
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
        VulkanDescriptorSetInfo setinfo{};
        setinfo.sampler = obj->texture->sampler;
        setinfo.imageView = obj->texture->imageView;
        setinfo.bufferView = obj->matrix.get();
        obj->descriptor = render->CreateDescriptor(&setinfo);
    }

    VulkanRenderObjectFactory::~VulkanRenderObjectFactory()
    {
    }
}