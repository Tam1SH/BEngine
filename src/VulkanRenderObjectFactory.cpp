#include <boost/filesystem.hpp>
#include <tbb.h>
module VulkanRenderObjectFactory;
import RenderObjects;
import CreateInfoStructures;

import VulkanRender;
import VulkanTextureFactory;
import RenderWorld;
import CommandPool;
import VulkanBuffer;
import Vertex;
import VulkanRenderBufferArray;
import MeshFactory;
import Vector2;
import <optional>;
import <memory>;
using std::optional;
using std::shared_ptr;


//#include <stb-master/stb_image_write.h>
namespace BEbraEngine {

    optional<RenderObject*> VulkanRenderObjectFactory::create(const RenderObjectCreateInfo& info)
    {
        
        auto maybe_object_view = _poolofObjects->get();
        shared_ptr<RenderBufferView> object_view;
        
        if (maybe_object_view.has_value()) {
            object_view = maybe_object_view.value();
        }
        else {

            //DEBUG_LOG2("BufferPool is empty", &_poolofObjects, "VulkanRenderObject", Debug::ObjectType::RenderObject, Debug::MessageType::Error);
            return optional<RenderObject*>();
        }
        
        auto obj = new VulkanRenderObject();
        obj->setName("RenderObject");
        obj->model = meshFactory->getDefaultModel("BOX");
        
        obj->matrix = object_view;
        obj->material = new Material(textureFactory->createEmpty(), textureFactory->createEmpty(), textureFactory->createEmpty());
        obj->hasMaps = false;
        obj->setColor(Vector3(1));
        VulkanDescriptorSetInfo setinfo{};
        setinfo.bufferView = object_view.get();
        
        setinfo.image = &obj->material->getColor().as<VulkanTexture>();
        
        setinfo.specular = &obj->material->getSpecular().as<VulkanTexture>();
        setinfo.normal = &obj->material->getNormal().as<VulkanTexture>();
        obj->descriptor = render->createDescriptor(&setinfo);
        
        if (!obj->descriptor) {
            //DEBUG_LOG2("Can't create render object", 0, "VulkanRenderObject", Debug::ObjectType::RenderObject, Debug::MessageType::Error);
            delete obj;
            return optional<RenderObject*>();
        }
        obj->layout = &render->pipelineLayout;
        return optional<RenderObject*>(obj);
        
    }

    Light* VulkanRenderObjectFactory::createLight(const Vector3& color, const Vector3& position)
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
        
        throw std::exception();
    }

    void VulkanRenderObjectFactory::setContext(Render* render)
    {
        
        this->render = dynamic_cast<VulkanRender*>(render);

        textureFactory = new VulkanTextureFactory(render);
       

        _poolofObjects = std::make_unique<VulkanRenderBufferArray<RenderObject::ShaderData>>();
        _poolofObjects->setContext(render);
        _poolofObjects->setUsage(RenderBufferPoolUsage::SeparateOneBuffer);
        _poolofObjects->allocate(10000, sizeof(RenderObject::ShaderData), Render::TypeBuffer::Storage);
        
        _poolofDirLights = std::make_unique<VulkanRenderBufferArray<DirectionLight::ShaderData>>();
        _poolofDirLights->setContext(render);
        _poolofDirLights->allocate(1, sizeof(DirectionLight::ShaderData), Render::TypeBuffer::Storage);

        _poolofPointLights = std::make_unique<VulkanRenderBufferArray<Light::ShaderData>>();
        _poolofPointLights->setContext(render);
        _poolofPointLights->setUsage(RenderBufferPoolUsage::SeparateOneBuffer);
        _poolofPointLights->allocate(10000, sizeof(Light::ShaderData), Render::TypeBuffer::Storage);


        meshFactory = std::unique_ptr<MeshFactory>(new MeshFactory(render));

        
        auto v = RenderBufferView();
        v.buffer = _poolofPointLights->getBuffer();
        v.availableRange = sizeof(Light::ShaderData) * 100;

        auto info = LightDescriptorInfo();
        info.bufferView = &v;
        info.type = LightDescriptorInfo::Type::Point;
        
    }

    void VulkanRenderObjectFactory::setWorld(RenderWorld& world)
    {
        this->world = &world;
    }

    void VulkanRenderObjectFactory::destroyObject(RenderObject& object)
    {
        
        auto& obj = object.as<VulkanRenderObject>();
        render->freeDescriptor(obj);
        _poolofObjects->free(obj.matrix);
        obj.matrix = 0;
#ifdef _DEBUG
       // object.isDestroyed = true;
#endif // _DEBUG
        
    }

    void VulkanRenderObjectFactory::destroyPointLight(Light& light)
    {
        auto& light_ = light.as<VulkanPointLight>();
        _poolofPointLights->free(light_.data);
    }

    void VulkanRenderObjectFactory::destroyCamera(SimpleCamera& camera)
    {
    }

    TextureFactory& VulkanRenderObjectFactory::getTextureFactory()
    {
        return *textureFactory;
    }

    optional<Material*> VulkanRenderObjectFactory::createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info)
    {
        
        //Не принципиально удалён ли был объект или нет
        auto wObj = std::weak_ptr<RenderObject>(obj);
        auto pointer = &*obj;
        auto mat = textureFactory->createMaterialAsync(info, [=](Material* mat) {
            render->executeQueues.addTask(ExecuteType::Multi,
                [=] { 
                    if (!wObj.expired()) {
                        auto& vObj = wObj.lock()->as<VulkanRenderObject>();
                        
                        setMaterial(vObj, *mat);
                        world->updateState({});
                    }
                    else {
                        //DEBUG_LOG3("Render object was destroyed during set material", pointer);
                        //mat->destroy(*destroyer);
                        delete mat;
                    }
                });
            
        });

        return optional<Material*>(mat);
        
    }



    void VulkanRenderObjectFactory::setMaterial(RenderObject& obj, Material& material)
    {
        
        auto& vObj = obj.as<VulkanRenderObject>();

        if (vObj.material) {
            //vObj.material->destroy(*destroyer);
            delete vObj.material;
        }
        if (!vObj.matrix) {
            //DEBUG_LOG1("Probably object has been destroyed while seting material");
            return;
        }
        vObj.hasMaps = true;
        VulkanDescriptorSetInfo setinfo{};
        setinfo.bufferView = obj.matrix.get();
        setinfo.image = &material.getColor().as<VulkanTexture>();
        setinfo.specular = &material.getSpecular().as<VulkanTexture>();
        setinfo.normal = &material.getNormal().as<VulkanTexture>();
        render->freeDescriptor(vObj);
        
        vObj.descriptor = render->createDescriptor(&setinfo);

        vObj.material = &material;
        
    }

    void VulkanRenderObjectFactory::setComponentDestroyer(VisitorGameComponentDestroyer& destroyer)
    {
        this->destroyer = &destroyer;
        textureFactory->setDestroyer(destroyer);
    }

    void VulkanRenderObjectFactory::bindTransform(Light& light, Transform& transform)
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
        setinfo.bufferView = obj->matrix.get();
        obj->descriptor = render->createDescriptor(&setinfo);
        
    }

    VulkanRenderObjectFactory::VulkanRenderObjectFactory()
    {

    }

    VulkanRenderObjectFactory::~VulkanRenderObjectFactory()
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
        
        throw std::exception();
    }

    void VulkanRenderObjectFactory::setModel(RenderObject& object, const std::string& path)
    {
        
        object.model.reset();
        ModelCreateInfo info{};
        info.path = path;
        
        auto m = meshFactory->create(info);
        if (m.has_value()) {
            object.model = shared_ptr<Model>(m.value());
        }
        
    }
}

/*
auto imageMemory = static_cast<VulkanTexture&>(material.getSpecular()).memory;



VkMappedMemoryRange range{};
range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
range.memory= imageMemory;
range.size = material.getSpecular().width() * material.getSpecular().height();
range.offset = 0;

vkInvalidateMappedMemoryRanges(render->device, 1, &range);
unsigned char* memImage = new unsigned char[range.size];
void* memory{};

auto res = vkMapMemory(VulkanRender::device, imageMemory, range.offset, range.size, 0, &memory);
memcpy(&memImage, memory, range.size);
vkUnmapMemory(VulkanRender::device, imageMemory);
//textureFactory->jopa("JOPA.jpg", material.getSpecular().height(), material.getSpecular().width(), 3, memImage, 90);
*/