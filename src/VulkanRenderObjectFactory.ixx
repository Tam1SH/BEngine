

#include "platform.hpp"
#include <boost/filesystem.hpp>
#include <tbb.h>
#include <variant>

export module VulkanRenderObjectFactory;
import Light;
import Camera;
import RenderObject;
import Material;
import DirectionLight;
import Texture;
import Transform;
import VulkanTextureFactory;
import MeshFactory;
import RenderBuffer;
import VulkanRenderBufferArray;
import VulkanRender;
import VulkanRenderAllocator;
import RenderBufferArray;
import CRenderAllocator;
import CRender;
import Task;
import Model;

import <memory>;
import <string>;
import <optional>;
//разделить логику и создание/удаление(назв. Adjuster?) также для рендера создать чтоли стораге?
using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;


namespace BEbraEngine {
    
    export class VulkanRenderObjectFactory
    {
    public:
        Task<optional<Material*>> createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info);

        optional<RenderObject*> create(const RenderObjectCreateInfo& info);

        void setMaterial(RenderObject& obj, Material& material);

       // void setComponentDestroyer(VisitorGameComponentDestroyer& destroyer);

        void bindTransform(Light& light, Transform& transform);

        void bindTransform(RenderObject& object, Transform& transform);

        Light* createLight(const Vector3& color, const Vector3& position);

        DirectionLight* createDirLight(const Vector3& color, const Vector3& direction);

        SimpleCamera* createCamera(const Vector3& position);
       
        void destroyObject(RenderObject& object);

        void destroyPointLight(Light& light);

        void destroyCamera(SimpleCamera& camera);

        void setModel(RenderObject& object, const string& path);

        
        VulkanRenderObjectFactory(VulkanRender& render, VulkanRenderAllocator& allocator, MeshFactory&& meshFactory);

        VulkanRenderObjectFactory() {}
        ~VulkanRenderObjectFactory();

        VulkanRenderObjectFactory(VulkanRenderObjectFactory&&) noexcept = default;
        VulkanRenderObjectFactory& operator=(VulkanRenderObjectFactory&&) noexcept = default;

        VulkanRenderObjectFactory(const VulkanRenderObjectFactory&) noexcept = delete;
        VulkanRenderObjectFactory& operator=(const VulkanRenderObjectFactory&) noexcept = delete;


    private:
        unique_ptr<VulkanRenderBufferArray<RenderObject::ShaderData>> _poolofObjects;
        unique_ptr<VulkanRenderBufferArray<Light::ShaderData>> _poolofPointLights;
        unique_ptr<VulkanRenderBufferArray<DirectionLight::ShaderData>> _poolofDirLights;

        shared_ptr<RenderBufferView> storage;
        //VisitorGameComponentDestroyer* destroyer;
        VulkanRender* render;
        VulkanRenderAllocator* allocator;
        VulkanTextureFactory textureFactory;
        MeshFactory meshFactory;
        
    };

    namespace create {

        export std::variant<VulkanRenderObjectFactory> renderObjectFactory(CRender auto& render, CRenderAllocator auto& allocator, MeshFactory&& meshFactory) {
            static_assert("no implementation found, check type");
        }

        export template<> std::variant<VulkanRenderObjectFactory> renderObjectFactory(VulkanRender& render, VulkanRenderAllocator& allocator, MeshFactory&& meshFactory);
    }
}

module :private;
import CRenderObjectFactory;
namespace BEbraEngine {
    static_assert(CRenderObjectFactory<VulkanRenderObjectFactory>);
}
