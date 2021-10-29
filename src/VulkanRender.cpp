#include "stdafx.h"

#include "VulkanRender.hpp"

#include "RenderObject.hpp"

#include "GameObject.hpp"
#include "RigidBoby.hpp"
//#include "imgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_vulkan.h"

#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace BEbraEngine {
    

    void VulkanRender::Init() {
        ResizeDescriptorPool(countOfObject);
        // camera.SetRender(this);
        // creator.CreateStorageBuffer(sizeof(glm::mat4) * 2, camera.buffer);
        // camera.CreateCameraSet();
        // creator.SetImgsCreator(&creatorImgs);
        // Model::SetCreator(&creatorImgs);
        // VkObject::SetCreator(&creator);
        // RenderObject::SetFactory(&creator);
        for (int i = 0; i < 10; i++) {
            //      objs.push_back(GameObject::New(glm::vec3(i)));
            //     objs[i / 2]->GetComponent<RigidBody>()->SetDynamic(false);
        }
    }
    void VulkanRender::UpdateCamera() {
        //   camera.ProcessMouseMovement();
    }


    void VulkanRender::OnUpdateData()
    {
        t1 = Clock::now();
        float time = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t2).count() / 1000000.f;
        t2 = t1;

        //deltaTime = time;
      //  UpdateCamera();

        struct Pizda {
            alignas(16) glm::mat4 mat;
            alignas(16) glm::mat4 proj;

        };
        Pizda p;
        p.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.0001f, 10000.0f);
        p.proj[1][1] *= -1;
        // p.mat = camera.GetViewMatrix();

        void* data;

    }
    void VulkanRender::StartRender() {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

        for (int i = 0; i < swapChainFramebuffers.size(); i++) {
            if (vkBeginCommandBuffer(RenderBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }
            VkRenderPassBeginInfo renderPassInfo{};

            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = swapChainExtent;
            std::array<VkClearValue, 2> clearValues{};
            clearValues[0] = { 255 / 255.f, 174 / 255.f, 201 / 255.f, 1.0f };
            clearValues[1].depthStencil = { 1.0f, 0 };
            renderPassInfo.clearValueCount = clearValues.size();
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(RenderBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        }
    }
    void VulkanRender::EndRender() {
        for (int i = 0; i < swapChainFramebuffers.size(); i++) {
            vkCmdEndRenderPass(RenderBuffers[i]);
            vkEndCommandBuffer(RenderBuffers[i]);
        }
    }
    void VulkanRender::OnDrawFrame() {



        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

        for (int i = 0; i < swapChainFramebuffers.size(); i++) {
            if (vkBeginCommandBuffer(RenderBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }
            VkRenderPassBeginInfo renderPassInfo{};

            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = swapChainExtent;

            std::array<VkClearValue, 2> clearValues{};

            clearValues[0].color = { 255 / 255.f, 174 / 255.f, 201 / 255.f, 1.0f };
            clearValues[1].depthStencil = { 1.0f, 0 };
            renderPassInfo.clearValueCount = 2;
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(RenderBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdBindPipeline(RenderBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

            {
                vkCmdBindDescriptorSets(RenderBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &setMainCamera, 0, nullptr);

                //TODO: оверхед, нахуя так делать? Надо избавиться от этого ебаного цикла и сделать единственный дескриптор для динамических объектов 
                for (auto lock_object = objects.begin(); lock_object != objects.end(); ++lock_object) {
                    if (lock_object->expired()) {
                        lock_object = objects.erase(lock_object);
                        --lock_object;
                    }
                    else {
                        auto object = lock_object->lock();
                        
                        object->Draw(RenderBuffers[i]);
                    }

                }
          //      auto data = ImGui::GetDrawData();
           //     if (data)
           //         ImGui_ImplVulkan_RenderDrawData(data, RenderBuffers[i]);
            }
            vkCmdEndRenderPass(RenderBuffers[i]);
            vkEndCommandBuffer(RenderBuffers[i]);
            BufferQueue.push(RenderBuffers[i]);
        }


    }

    VulkanRender::VulkanRender() {

    }
    void VulkanRender::OnRecreateSwapChain() {
        CreateCameraSet(camera->cameraData);
        for (auto lock_object = objects.begin(); lock_object != objects.end(); ++lock_object) {
            auto object_ = *lock_object;
            if (object_.expired()) {
                lock_object = objects.erase(lock_object);
                --lock_object;

            }
            else {
                object_.lock()->Recreate();
            }

        }

    }
}