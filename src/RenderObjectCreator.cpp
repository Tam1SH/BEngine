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

    RenderObject* VulkanRenderObjectFactory::create(RenderObjectInfo* info)
    {
        auto factory = MeshFactory();

        auto obj = new VulkanRenderObject();
        obj->name = "RenderObject";
        
        obj->mesh = std::unique_ptr<Mesh1>(new Mesh1());
        obj->model = std::unique_ptr<Model>(factory.create("C:/.BEbraEngine/src/Models/BOX_NAXYU.fbx").value());
        obj->mesh->VBO = render->CreateVertexBuffer(obj->model->meshes[0].vertices);
        obj->mesh->EBO = render->CreateIndexBuffer(obj->model->meshes[0].indices);
        obj->texture = std::unique_ptr<Texture>(imgsCreator->createEmptyTexture());
        obj->matrix = std::shared_ptr<RenderBufferView>(info->bufferView);

        VulkanDescriptorSetInfo setinfo{};
        setinfo.sampler = obj->texture->sampler;
        setinfo.imageView = obj->texture->imageView;
        setinfo.bufferView = info->bufferView;

        obj->descriptor = render->CreateDescriptor(&setinfo);
        obj->layout = &render->pipelineLayout;
        return obj;
    }

    void VulkanRenderObjectFactory::BindTransform(RenderObject* object, Transform* transform)
    {
        transform->buffer = object->matrix;
    }

    RenderObject* VulkanRenderObjectFactory::createObject()
    {
        auto _obj = _pool->get();
        if (_obj.has_value()) {
            auto renderObject = _obj.value();
            return renderObject;
        }
        else {
            Debug::Log("Pool is empty");
            throw std::exception();
        }
    }
    void VulkanRenderObjectFactory::CreateObjectSet(VulkanRenderObject* obj)
    {
        VulkanDescriptorSetInfo setinfo{};
        setinfo.sampler = obj->texture->sampler;
        setinfo.imageView = obj->texture->imageView;
        setinfo.bufferView = obj->matrix.get();
        obj->descriptor = render->CreateDescriptor(&setinfo);
    }

    VulkanRenderObjectFactory::VulkanRenderObjectFactory(std::shared_ptr<VulkanRender> render) : render(render)
    {
        VulkanRenderObject::SetFactory(this);
        imgsCreator = new TextureFactory(render.get());

        _pool = std::make_unique<VulkanRenderObjectPool>();
        _pool->setContext(render.get());
        _pool->setFactory(this);

        _pool->allocate(10);
    }
    VulkanRenderObjectFactory::~VulkanRenderObjectFactory()
    {
    }
}