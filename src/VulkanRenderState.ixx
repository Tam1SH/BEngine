module;
#include <expected.hpp>
export module VulkanRenderState;
import VulkanRenderBufferArray;
import RenderObject;
import CRenderState;
import Error;
import Light;
import DirectionLight;
import <memory>;

using std::shared_ptr;

namespace BEbraEngine {

    export struct VulkanRenderStateCreateInfo : RenderStateCreateInfo {};

    export struct VulkanRenderState {

        tl::expected<void, CreateStateError> create(const RenderStateCreateInfo& info) {
            return tl::make_unexpected(CreateStateError{ CreateStateErrorCode{} ,"LOL" });
        }
        void clear() {

        }

        VulkanRenderBufferArray<RenderObject::ShaderData> _poolofObjects;
        VulkanRenderBufferArray<Light::ShaderData> _poolofPointLights;
        VulkanRenderBufferArray<DirectionLight::ShaderData> _poolofDirLights;
        shared_ptr<RenderBufferView> storage;
        //VisitorGameComponentDestroyer* destroyer;
    };
}