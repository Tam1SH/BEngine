#include <boost/pool/object_pool.hpp>;
export module VulkanRenderObjectFactory;
import Light;
import Camera;
import Material;
import DirectionLight;
import Transform;
import RenderBuffer;
import VulkanRenderBufferArray;
import VulkanRenderAllocator;
import RenderBufferArray;

import CreateInfoStructures;
import VulkanRenderState;
import AllocationStrategy;
import Task;
import Model;
import Vector3;
import RenderObjectFactory;
import <optional>;
import <variant>;
import <memory>;
import <string>;

//разделить логику и создание/удаление(назв. Adjuster?) также для рендера создать чтоли стораге?
using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;


namespace BEbraEngine {
    export struct VulkanRender;
    export struct VulkanTextureFactory;
    export struct MeshFactory;
    export struct RenderObject;
    export struct RenderObjectCreateInfo;
}

namespace BEbraEngine {
    
    export struct VulkanRenderObjectFactory : public RenderObjectFactory, private AllocationStrategy<EnumAllocationStrategy::Any>
    {
        Task<optional<Material*>> createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info) override;

        optional<RenderObject*> create(const RenderObjectCreateInfo& info) override;

        optional<Light*> createLight(const LightCreateInfo& info) override;

        optional<DirectionLight*> createDirLight(const DirectionLightCreateInfo& info) override;

        optional<SimpleCamera*> createCamera(const CameraCreateInfo& info) override;

        void setMaterial(RenderObject& obj, Material& material);

        void bindTransform(Light& light, Transform& transform);

        void bindTransform(RenderObject& object, Transform& transform);
       
        void destroyObject(RenderObject& object);

        void destroyPointLight(Light& light);

        void destroyCamera(SimpleCamera& camera);

        void setModel(RenderObject& object, const string& path);

        VulkanRenderObjectFactory(VulkanRender& render, VulkanRenderAllocator& allocator, 
                                  MeshFactory& meshFactory, VulkanTextureFactory& factory);

        VulkanRenderObjectFactory() {}
        ~VulkanRenderObjectFactory();

        VulkanRenderObjectFactory(VulkanRenderObjectFactory&&) noexcept = default;
        VulkanRenderObjectFactory& operator=(VulkanRenderObjectFactory&&) noexcept = default;

        VulkanRenderObjectFactory(const VulkanRenderObjectFactory&) noexcept = delete;
        VulkanRenderObjectFactory& operator=(const VulkanRenderObjectFactory&) noexcept = delete;

    private:

        VulkanRender* render;
        VulkanRenderAllocator* allocator;
        VulkanRenderState* state;
        VulkanTextureFactory* textureFactory;
        MeshFactory* meshFactory;
        
    };
}

