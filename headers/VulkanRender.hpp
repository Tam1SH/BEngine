#pragma once

#include "stdafx.h"
#include "platform.hpp"
#include "AbstractRender.hpp"
#include "ExecuteQueues.hpp"
#include "Vector2.hpp"
#include "RenderObject.hpp"
#undef min
#undef max

class btIDrawDebug;

const int MAX_FRAMES_IN_FLIGHT = 1;

namespace BEbraEngine {
    class VulkanTexture;
    class Matrix4;
    class VulkanWindow;
    class SimpleCamera;
    class VulkanCamera;
    class RenderBuffer;
    class Vertex;
    class RenderObject;
    class Light;
    class DirectionLight;
    class VulkanDescriptorSetInfo;
    class VulkanRenderObject;
    class LightDescriptorInfo;
    class DescriptorPool;
    class CommandPool;
    class VulkanPipeline;
    class CommandBuffer;
    class VulkanDirLight;
    class VulkanPointLight;
    class VulkanRenderObjectFactory;

    template<typename RenderData>
    class VulkanRenderBufferPool;

    class RenderBufferView;
    class Line;

}


using BE_STD::shared_ptr;
using BE_STD::unique_ptr;
using BE_STD::vector;
using BE_STD::function;
using BE_STD::optional;
using BE_STD::map;
using BE_STD::list;
using BE_STD::string;
using BE_STD::atomic;

BE_NAMESPACE_STD_BEGIN
    template<typename T, typename D>
    class unique_ptr;
    template<class T>
    class shared_ptr;
    template<class T, typename Alloc> 
    class list;
BE_NAMESPACE_STD_END



namespace BEbraEngine {


    class VulkanRender final : public AbstractRender
    {
    public:
       
        void create(BaseWindow* window) override;

        void destroyBuffer(RenderBuffer* buffer) override;

        RenderBuffer* createUniformBuffer(uint32_t size) override;

        RenderBuffer* createStorageBuffer(uint32_t size) override;

        RenderBuffer* createIndexBuffer(vector<uint32_t> indices) override;

        RenderBuffer* createVertexBuffer(vector<Vertex> vertices) override;

        void addCamera(SimpleCamera& camera) override;

        void selectMainCamera(SimpleCamera& camera) override;

        void removeCamera(SimpleCamera& camera) override;

        AbstractRender::Type getType() override { return AbstractRender::Type::Vulkan; }

        IRenderObjectFactory* getRenderObjectFactory() override;

        void addGlobalLight(DirectionLight& globalLight) override;

        void drawFrame() override;

        void update() override;

        void updateState(RenderData& data) override;

        void drawLine(const Vector3& from, const Vector3& to, const Vector3& color) override;


        Vector2 getCurrentRenderResolution() { 
            return { 
            static_cast<float>(currentRenderResolution.width), 
            static_cast<float>(currentRenderResolution.height) 
            };
        }

        uint32_t alignmentBuffer(uint32_t originalSize, AbstractRender::TypeBuffer type) override;

        VkDescriptorSet createDescriptor(VulkanDescriptorSetInfo* info);

        void updateDesriptor(VkDescriptorSet& set, VulkanDescriptorSetInfo* info);

        VkDescriptorSet createDescriptor(LightDescriptorInfo* info);

        VkDescriptorSet createDescriptor2(RenderBufferView* buffer);

        VkDescriptorSet createDescriptor(RenderBuffer* buffer);

        void freeDescriptor(VulkanRenderObject& set);

        void freeDescriptor(VulkanDirLight* set);

        void freeDescriptor(VulkanPointLight* set);

        void destroyTexture(VulkanTexture& texture);

        RenderBuffer* createBufferAsync(void* data, uint32_t size, VkBufferUsageFlags usage);

        void generateMipmaps(VulkanTexture* texture, VkFormat imageFormat, CommandBuffer& buffer);

        void createVkImage(unsigned char* data, VulkanTexture* texture, VkDeviceSize imageSize);

        VkImageView createImageView(VulkanTexture* texture, VkFormat format, VkImageAspectFlags aspectFlags);

        void createTextureSampler(VulkanTexture* texture);
        
        VulkanTexture* ImageFromGpuToCpuMemory(VulkanTexture* texture);

        void recreateSwapChain(uint32_t width, uint32_t height);

        VkPipelineLayout pipelineLayout;

        ExecuteQueues<function<void()>> executeQueues_Objects;

    public:
        enum class DescriptorLayoutType {
            Object,
            SimpleCamera,
            LightPoint,
            DirectionLight,
            Attachments,
            PhysicsDebug
        };
        struct QueueFamilyIndices {
            
            optional<uint32_t> graphicsFamily;
            optional<uint32_t> presentFamily;
            optional<uint32_t> transferFamily;
            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value() && transferFamily.has_value();
            }
        };

        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            vector<VkSurfaceFormatKHR> formats;
            vector<VkPresentModeKHR> presentModes;
        };

        struct ScreenAttachments {
            unique_ptr<VulkanTexture> color;
            unique_ptr<VulkanTexture> depth;
            unique_ptr<VulkanTexture> normal;
        };

        VulkanRender();

        ~VulkanRender();

        
    public:

        static VkDevice device;

        static VkPhysicalDevice physicalDevice;

        static VkInstance instance;

        static QueueFamilyIndices FamilyIndices;

    
    private:
        mutex m;

        bool needCmdBuffersUpdate{ true };

        float totalTime;

        VkDescriptorSet lineSet;

        atomic<size_t> linesToDraw{0};

        atomic<size_t> linesToDrawLastUpdate;

        VkDescriptorSet objectSet;

        vector<Line::ShaderData> linesMemory{ 30000 };

        unique_ptr<VulkanRenderBufferPool<Line::ShaderData>> linePool;

        unique_ptr<VulkanRenderObjectFactory> factory;

        list<VulkanCamera*> cameras;

        VulkanDirLight* globalLight;

        VulkanWindow* window;

        VkPipeline graphicsPipeline;

        VkPipeline linesDrawing;

        VkPipeline graphicsPipeline2;

        shared_ptr<RenderBuffer> cameraPlug;

        unique_ptr<DescriptorPool> vulkanRenderBufferPool;

        vector<unique_ptr<DescriptorPool>> renderObjectsPools;

        unique_ptr<DescriptorPool> cameraPool;

        unique_ptr<DescriptorPool> attachmentsSetPool;

        unique_ptr<DescriptorPool> lightPool;

        unique_ptr<DescriptorPool> PhysicsDebugPool;

        vector<unique_ptr<CommandPool>> concurrentCommandPools_RenderQueue;

        unique_ptr<CommandPool> swapChainRenderCommandPool;

        vector<unique_ptr<CommandPool>> concurrentCommandPools_TransferQueue;

        VkExtent2D currentRenderResolution;

        VkDescriptorSet setMainCamera;

        VkDescriptorSet globalLightSet;

        VkDescriptorSet pointLightsSet;

        VkDescriptorSet physicsDebugSet;

        vector<VkDescriptorSet> attachmentsSets;

        vector<unique_ptr<VulkanTexture>> normalAttachments;

        vector<unique_ptr<VulkanTexture>> colorAttachments;

        vector<unique_ptr<VulkanTexture>> depthAttachments;

        uint32_t MAX_COUNT_OF_OBJECTS = 1000;

        uint32_t MAX_COUNT_OF_LIGHTS = 100;

        VkDebugUtilsMessengerEXT debugMessenger;

        VkSurfaceKHR surface;

        tbb::concurrent_queue<CommandBuffer> BufferRenderQueue;

        tbb::concurrent_queue<CommandBuffer> BufferTransferQueue;

        VkQueue graphicsQueue;

        VkQueue transferQueue;

        VkQueue presentQueue;

        VkSwapchainKHR swapChain;

        vector<VkImage> swapChainImages;

        VkFormat swapChainImageFormat;

        

        vector<VkImageView> swapChainImageViews;

        vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;
        
        VkRenderPass resolutionScaling;

        map<DescriptorLayoutType, VkDescriptorSetLayout> layouts;

        VkDescriptorSetLayout ObjectWithoutTextureLayout;

        VkDescriptorSetLayout ObjectLayout;

        VkDescriptorSetLayout CameraLayout;

        VkDescriptorSetLayout LightLayout;

        unique_ptr<VulkanPipeline> pipeLine;
        
        VkCommandPool _commandPool;

        VkCommandBuffer _copyBuffer;

        vector<CommandBuffer> RenderBuffers;

        vector<VkSemaphore> imageAvailableSemaphores;

        vector<VkSemaphore> renderFinishedSemaphores;

        vector<VkFence> inFlightFences;

        vector<VkFence> imagesInFlight;

        VkPhysicalDeviceProperties GPU_properties;


        size_t currentFrame = 0;

    private:

        void createCameraSet(); 

        void createPointAndDirectionLightsSets();

        VkQueue getGraphicsQueue();

        void addBufferToRenderQueue(const CommandBuffer& buffer);

        void addBufferToTransferQueue(const CommandBuffer& buffer);

        VkFence* getCurrentFence();

        void recreateRenderObjects();

        //TODO: потеряла свой смысл.
        void createDepthResources();

        VkFormat findSupportedFormat(const vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        VkFormat findDepthFormat();

        bool hasStencilComponent(VkFormat format);

        static void _createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        void copyBuffer1(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandBuffer& cmdBuffer);

        //static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        VkDevice getDevice();

        static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createImage(VulkanTexture* texture, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);

        void transitionImageLayout(VulkanTexture* texture, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandBuffer& buffer);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandBuffer& cmdbuffer);
       
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        void createInstance();

        void createPools();

        void cleanupSwapChain();

        void cleanUpDefault();

        void createAllDescriptorLayouts();

        void createTextureDescriptorSetLayout();

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        void setupDebugMessenger();

        void pickPhysicalDevice();

        void createLogicalDevice();

        void createSwapChain(uint32_t width, uint32_t height);

        void createImageViews();

        void createAttachment(VkFormat format, VkImageUsageFlags usage, VulkanTexture* attachment);

        void createRenderPass();

        void createAttachmentsSet();

        void createGraphicsPipeline();

        void createFramebuffers();

        void createCommandPool();

        void createPhysicsDebugDescriptorSetLayout();

        void createObjectDescriptorSetLayout();

        void createLightDescriptorSetLayout();

        void createCameraDescriptorSetLayout();

        void createSyncObjects();

        void createCmdBuffers();

        void updateCmdBuffers(RenderData& data);

        VkShaderModule createShaderModule(const vector<char>& code);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const vector<VkSurfaceFormatKHR>& availableFormats);

        VkPresentModeKHR chooseSwapPresentMode(const vector<VkPresentModeKHR>& availablePresentModes);


        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        bool isDeviceSuitable(VkPhysicalDevice device);

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        vector<const char*> getRequiredExtensions();

        bool checkValidationLayerSupport();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

        static vector<char> readFile(const string& filename);

        VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

        const vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        const bool enableValidationLayers = true;

    };

}