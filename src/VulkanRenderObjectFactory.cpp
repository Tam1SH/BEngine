#include "stdafx.h"
#include "RenderObject.hpp"
#include "VulkanRenderObjectFactory.hpp"
#include "CreateInfoStructures.hpp"
#include "VulkanRender.hpp"
#include "VulkanTextureFactory.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "VkBuffer.hpp"
#include "VulkanObjects.hpp"
#include "Vertex.hpp"
#include "VulkanRenderBufferPool.hpp"
#include "Debug.hpp"
#include "MeshFactory.hpp"
#include "Vector2.hpp"

namespace BEbraEngine {

    optional<RenderObject*> VulkanRenderObjectFactory::create(const RenderObject::RenderObjectCreateInfo& info)
    {

        auto maybe_object_view = _poolofObjects->get();
        shared_ptr<RenderBufferView> object_view;

        if (maybe_object_view.has_value()) {
            object_view = maybe_object_view.value();
        }
        else {

            DEBUG_LOG2("BufferPool is empty", &*_poolofObjects, "VulkanRenderObject", Debug::ObjectType::RenderObject, Debug::MessageType::Error);
            return optional<RenderObject*>();
        }

        auto obj = new VulkanRenderObject();
        obj->setName("RenderObject");
        obj->model = meshFactory->getDefaultModel("BOX");
        obj->texture = unique_ptr<Texture>(textureFactory->createEmpty());

        obj->matrix = object_view;

        obj->setColor(Vector3(0.2f, 0.4f, 0.3f));
        VulkanDescriptorSetInfo setinfo{};
        auto vTex = static_cast<VulkanTexture*>(obj->texture.get());
        setinfo.sampler = vTex->sampler;
        setinfo.imageView = vTex->imageView;
        setinfo.bufferView = object_view.get();

        obj->descriptor = render->createDescriptor(&setinfo);
        if (!obj->descriptor) {
            DEBUG_LOG2("Can't create render object", 0, "VulkanRenderObject", Debug::ObjectType::RenderObject, Debug::MessageType::Error);
            delete obj;
            return optional<RenderObject*>();
        }
        obj->layout = &render->pipelineLayout;
        return optional<RenderObject*>(obj);
    }

    PointLight* VulkanRenderObjectFactory::createLight(const Vector3& color, const Vector3& position)
    {
        auto maybe_object_view = _poolofPointLights->get();
        shared_ptr<RenderBufferView> object_view;
        if (maybe_object_view.has_value()) {
            object_view = maybe_object_view.value();
        }
        else throw std::runtime_error("");
        auto light = new VulkanPointLight();
        light->setColor(color);
        light->data = object_view;

        return light;
    }

    DirectionLight* VulkanRenderObjectFactory::createDirLight(const Vector3& color, const Vector3& direction)
    {
        auto maybe_light_view = _poolofDirLights->get();
        shared_ptr<RenderBufferView> view;

        if (maybe_light_view.has_value()) {
            view = maybe_light_view.value();
        }

        auto light = new VulkanDirLight();
        light->setColor(color);
        light->setDirection(direction);


        auto info = LightDescriptorInfo();
        info.bufferView = view.get();
        info.type = LightDescriptorInfo::Type::Direction;

        light->data = view;
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
        _poolofPointLights->allocate(10000, sizeof(PointLight::ShaderData) * 10000, AbstractRender::TypeBuffer::Storage);


        meshFactory = std::unique_ptr<MeshFactory>(new MeshFactory(render));

        
        auto v = RenderBufferView();
        v.buffer = _poolofPointLights->getBuffer();
        v.availableRange = sizeof(PointLight::ShaderData) * 100;

        auto info = LightDescriptorInfo();
        info.bufferView = &v;
        info.type = LightDescriptorInfo::Type::Point;
    }

    void VulkanRenderObjectFactory::destroyObject(RenderObject& object)
    {
        auto& obj = static_cast<VulkanRenderObject&>(object); 
        render->freeDescriptor(obj);
        _poolofObjects->free(obj.matrix);
        auto texture = obj.texture;

        render->executeQueues_Objects.addTask(ExecuteType::Multi,
            [=] {
            if (texture.get())
                textureFactory->destroyTexture(texture.get());
            else
                DEBUG_LOG2("Texture lost", 0, "", Debug::ObjectType::RenderObject, Debug::MessageType::Error);
            });

#ifdef _DEBUG
        object.isDestroyed = true;
#endif // _DEBUG

    }

    void VulkanRenderObjectFactory::destroyPointLight(PointLight& light)
    {
        auto& light_ = static_cast<VulkanPointLight&>(light);
        _poolofPointLights->free(light_.data);
    }

    void VulkanRenderObjectFactory::destroyCamera(SimpleCamera& camera)
    {
    }

    void VulkanRenderObjectFactory::bindTransform(PointLight& light, Transform& transform)
    {
        light.transform = &transform;
    }
    void VulkanRenderObjectFactory::bindTransform(RenderObject& object, Transform& transform)
    {
        object.transform = &transform;
    }

    void VulkanRenderObjectFactory::CreateObjectSet(VulkanRenderObject* obj)
    {
        render->freeDescriptor(*obj);
        VulkanDescriptorSetInfo setinfo{};
        auto vTex = static_cast<VulkanTexture*>(obj->texture.get());
        setinfo.sampler = vTex->sampler;
        setinfo.imageView = vTex->imageView;
        setinfo.bufferView = obj->matrix.get();
        obj->descriptor = render->createDescriptor(&setinfo);
    }

    VulkanRenderObjectFactory::VulkanRenderObjectFactory()
    {

    }

    VulkanRenderObjectFactory::~VulkanRenderObjectFactory()
    {

    }

    void VulkanRenderObjectFactory::setTexture(shared_ptr<RenderObject> object, const boost::filesystem::path& path)
    {
        shared_ptr<VulkanRenderObject> obj = std::static_pointer_cast<VulkanRenderObject>(object);


        Texture* _texture = textureFactory->createAsync(path,
            [=](Texture* texture) {
                render->executeQueues_Objects.addTask(ExecuteType::Multi,
                    [=] {
                    if (obj.get()) {
                        auto eba = obj.get();
                        textureFactory->destroyTexture(eba->texture.get());
                        eba->texture.reset();
                        eba->texture = unique_ptr<Texture>(texture);
                        render->freeDescriptor(*eba);
                        VulkanDescriptorSetInfo setinfo{};

                        auto vTex = static_cast<VulkanTexture*>(eba->texture.get());
                        setinfo.sampler = vTex->sampler;
                        setinfo.imageView = vTex->imageView;
                        setinfo.bufferView = eba->matrix.get();
                        eba->descriptor = render->createDescriptor(&setinfo);
                    }
                    else
                        DEBUG_LOG2("Object has destroyed when it was being updated texture", 
                            texture,"", Debug::ObjectType::RenderObject, Debug::MessageType::Error);
                    });
            });

        object->texture = unique_ptr<Texture>(_texture);
    }

    void VulkanRenderObjectFactory::setTexture(shared_ptr<RenderObject> object, Texture const& path)
    {

    }

    SimpleCamera* VulkanRenderObjectFactory::createCamera(const Vector3& position)
    {
        auto camera = new VulkanCamera(render->getCurrentRenderResolution(), position);
        auto view = new RenderBufferView();
        view->availableRange = sizeof(SimpleCamera::ShaderData);
        view->buffer = shared_ptr<RenderBuffer>(render->createStorageBuffer(sizeof(SimpleCamera::ShaderData)));
        camera->cameraData = view;
        camera->descriptor = render->createDescriptor(camera->cameraData->buffer.get());
        return camera;
    }

    void VulkanRenderObjectFactory::setModel(RenderObject& object, const std::string& path)
    {
        object.model.reset();
        auto m = meshFactory->create(path);
        if (m.has_value()) {
            object.model = shared_ptr<Model>(m.value());
        }
    }
}