

#include "platform.hpp"
#include <boost/filesystem.hpp>

#include <variant>

export module VulkanRenderObjectFactory;
import Light;
import Camera;
import <tbb.h>;
import <boost/pool/object_pool.hpp>;
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
import Render;
import VulkanRenderState;
import AllocationStrategy;
import Task;
import Model;
import Vector3;

import <memory>;
import <string>;
import <optional>;
//разделить логику и создание/удаление(назв. Adjuster?) также для рендера создать чтоли стораге?
using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;


namespace BEbraEngine {
    


    export struct VulkanRenderObjectFactory : AllocationStrategy
    {
        Task<optional<Material*>> createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info);

        optional<RenderObject*> create(const RenderObjectCreateInfo& info);

        Light* createLight(const Vector3& color, const Vector3& position);

        DirectionLight* createDirLight(const Vector3& color, const Vector3& direction);

        SimpleCamera* createCamera(const Vector3& position);

        void setMaterial(RenderObject& obj, Material& material);

        void bindTransform(Light& light, Transform& transform);

        void bindTransform(RenderObject& object, Transform& transform);
       
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

        VulkanRender* render;
        VulkanRenderAllocator* allocator;
        VulkanRenderState* state;
        VulkanTextureFactory textureFactory;
        MeshFactory meshFactory;
        
    };

    namespace create {


        export std::variant<VulkanRenderObjectFactory> renderObjectFactory(Render& render, CRenderAllocator auto& allocator, MeshFactory&& meshFactory) {
            static_assert("no implementation found, check type");
        }

        export template<> std::variant<VulkanRenderObjectFactory> renderObjectFactory(Render& render, VulkanRenderAllocator& allocator, MeshFactory&& meshFactory);
    }
}

module :private;
import CRenderObjectFactory;
namespace BEbraEngine {
    //static_assert(CRenderObjectFactory<VulkanRenderObjectFactory>);
}
