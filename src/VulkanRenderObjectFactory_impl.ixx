#include <variant>
#include <boost/pool/object_pool.hpp>;
export module VulkanRenderObjectFactory_impl;
import VulkanObjects;
import VulkanRenderObjectFactory;
import Logger;
import RenderObject;
import Render;
import <optional>;
using std::optional;
using std::shared_ptr;


//#include <stb-master/stb_image_write.h>
namespace BEbraEngine {
    
    optional<RenderObject*> VulkanRenderObjectFactory::create(const RenderObjectCreateInfo& info)
    {
        auto maybe_object_view = with<optional<shared_ptr<RenderBufferView>>>({
            std::make_pair(EnumAllocationStrategy::AbsolutelyDontCare, [&]() {
                 return state->_poolofObjects.get();
            })
        });

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
        obj->material = new Material(textureFactory.createEmpty(), textureFactory.createEmpty(), textureFactory.createEmpty());
        obj->hasMaps = false;
        obj->setColor(Vector3(1));

        VulkanDescriptorSetInfo setinfo{};

        obj->descriptor = render->createDescriptor(VulkanDescriptorSetInfo::create(object_view.get(), *obj->material));
        //obj->layout = &render->pipelineLayout;

        if (!obj->descriptor) {
            //DEBUG_LOG2("Can't create renderAlloc object", 0, "VulkanRenderObject", Debug::ObjectType::RenderObject, Debug::MessageType::Error);
            delete obj;
            return optional<RenderObject*>();
        }

        return optional<RenderObject*>(obj);
        
    }

    

    Light* VulkanRenderObjectFactory::createLight(const Vector3& color, const Vector3& position)
    {
        auto maybe_object_view = state->_poolofPointLights.get();
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
        
        auto maybe_light_view = state->_poolofDirLights.get();
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




    void VulkanRenderObjectFactory::destroyObject(RenderObject& object)
    {
        
        auto& obj = object.as<VulkanRenderObject>();
        render->freeDescriptor(obj);
        state->_poolofObjects.free(obj.matrix);
        obj.matrix = 0;
#ifdef _DEBUG
       // object.isDestroyed = true;
#endif // _DEBUG
        
    }

    void VulkanRenderObjectFactory::destroyPointLight(Light& light)
    {
        auto& light_ = light.as<VulkanPointLight>();
        state->_poolofPointLights.free(light_.data);
    }

    void VulkanRenderObjectFactory::destroyCamera(SimpleCamera& camera)
    {
    }

    Task<optional<Material*>> VulkanRenderObjectFactory::createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info)
    {
        
        auto task = textureFactory.createMaterialAsync(info).
            then([=](optional<Material*> mat) {

                mat.and_then([&](Material* mat) -> optional<Material*> {
                        //render->executeQueues.addTask(ExecuteType::Multi,
                        //    [=]() { setMaterial(*obj, *mat); });

                        return std::make_optional(mat);
                });

            });

        return task;
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
        auto setinfo = VulkanDescriptorSetInfo::create(vObj.matrix.get(), material);
        render->freeDescriptor(vObj);
        vObj.descriptor = render->createDescriptor(setinfo);
        vObj.material = &material;
        
    }

    void VulkanRenderObjectFactory::bindTransform(Light& light, Transform& transform)
    {
        light.transform = &transform;
    }
    void VulkanRenderObjectFactory::bindTransform(RenderObject& object, Transform& transform)
    {
        object.transform = &transform;
    }


    VulkanRenderObjectFactory::VulkanRenderObjectFactory(
        VulkanRender& render, VulkanRenderAllocator& allocator, MeshFactory& meshFactory
    )
        : render(&render), allocator(&allocator), meshFactory(&meshFactory)
    {
        textureFactory = VulkanTextureFactory(render);
        //state->_poolofObjects = VulkanRenderBufferArray<RenderObject::ShaderData>(allocator);
        //_poolofObjects->setContext(&allocator);
        state->_poolofObjects.setUsage(RenderBufferPoolUsage::SeparateOneBuffer);
        state->_poolofObjects.allocate(10000, sizeof(RenderObject::ShaderData), TypeRenderBuffer::Storage);

        //state->_poolofDirLights = VulkanRenderBufferArray<DirectionLight::ShaderData>(allocator);
        //_poolofDirLights->setContext(&allocator);
        state->_poolofDirLights.allocate(1, sizeof(DirectionLight::ShaderData), TypeRenderBuffer::Storage);

        //state->_poolofPointLights = VulkanRenderBufferArray<Light::ShaderData>(allocator);
        //_poolofPointLights->setContext(&allocator);
        state->_poolofPointLights.setUsage(RenderBufferPoolUsage::SeparateOneBuffer);
        state->_poolofPointLights.allocate(10000, sizeof(Light::ShaderData), TypeRenderBuffer::Storage);

       // auto v = RenderBufferView();
        //v.buffer = state->_poolofPointLights.getBuffer();
       // v.availableRange = sizeof(Light::ShaderData) * 100;

       // auto info = LightDescriptorInfo();
       // info.bufferView = &v;
       // info.type = LightDescriptorInfo::Type::Point;
    }

    VulkanRenderObjectFactory::~VulkanRenderObjectFactory()
    {

    }

    SimpleCamera* VulkanRenderObjectFactory::createCamera(const Vector3& position)
    {
        
        auto camera = new VulkanCamera(render->getCurrentRenderResolution(), position);
        auto view = new RenderBufferView();
        view->availableRange = sizeof(SimpleCamera::ShaderData);
       // view->buffer = shared_ptr<RenderBuffer>(render->createStorageBuffer(sizeof(SimpleCamera::ShaderData)));
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

vkInvalidateMappedMemoryRanges(renderAlloc->device, 1, &range);
unsigned char* memImage = new unsigned char[range.size];
void* memory{};

auto res = vkMapMemory(VulkanRender::device, imageMemory, range.offset, range.size, 0, &memory);
memcpy(&memImage, memory, range.size);
vkUnmapMemory(VulkanRender::device, imageMemory);
//textureFactory->jopa("JOPA.jpg", material.getSpecular().height(), material.getSpecular().width(), 3, memImage, 90);
*/