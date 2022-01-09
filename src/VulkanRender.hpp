#pragma once

#include "stdafx.h"
#include "AbstractRender.hpp"
#include "ExecuteQueues.hpp"
#include "Vector2.hpp"
#undef min
#undef max



const int MAX_FRAMES_IN_FLIGHT = 3;

namespace BEbraEngine {
    class VulkanTexture;
    class Matrix4;
    class VulkanWindow;
    class SimpleCamera;
    class VulkanCamera;
    class RenderBuffer;
    class Vertex;
    class RenderObject;
    class PointLight;
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
    class RenderBufferView;
}

namespace std {
    template<typename T, typename D>
    class unique_ptr;
    template<class T>
    class shared_ptr;
}

namespace BEbraEngine {


    class VulkanRender final : public AbstractRender
    {
    public:
       
        void create(BaseWindow* window) override;

        void destroyBuffer(RenderBuffer* buffer) override;

        RenderBuffer* createUniformBuffer(uint32_t size) override;

        RenderBuffer* createStorageBuffer(uint32_t size) override;

        RenderBuffer* createIndexBuffer(std::vector<uint32_t> indices) override;

        RenderBuffer* createVertexBuffer(std::vector<Vertex> vertices) override;

        void addObject(std::shared_ptr<RenderObject> object) override;

        void addLight(std::shared_ptr<PointLight> light) override;

        void removeObject(std::shared_ptr<RenderObject> object) override;

        void removeLight(std::shared_ptr<PointLight> light) override;

        void addCamera(std::shared_ptr<SimpleCamera> camera) override;

        void selectMainCamera(SimpleCamera* camera) override;

        void removeCamera(std::shared_ptr<SimpleCamera> camera) override;

        AbstractRender::Type getType() override { return AbstractRender::Type::Vulkan; }

        IRenderObjectFactory* getRenderObjectFactory() override;

        void addGlobalLight(std::shared_ptr<DirectionLight> globalLight) override;

        void drawFrame() override;

        Vector2 getCurrentRenderResolution() { 
            return { 
            static_cast<float>(currentRenderResolution.width), 
            static_cast<float>(currentRenderResolution.height) 
        };
        }

        uint32_t alignmentBuffer(uint32_t originalSize, AbstractRender::TypeBuffer type) override;

        VkDescriptorSet createDescriptor(VulkanDescriptorSetInfo* info);

        VkDescriptorSet createDescriptor(LightDescriptorInfo* info);

        VkDescriptorSet createDescriptor(RenderBuffer* buffer);

        void freeDescriptor(VulkanRenderObject* set);

        void freeDescriptor(VulkanDirLight* set);

        void freeDescriptor(VulkanPointLight* set);

        void destroyTexture(VulkanTexture* texture);

        RenderBuffer* createBufferAsync(void* data, uint32_t size, VkBufferUsageFlags usage);

        void generateMipmaps(VulkanTexture* texture, VkFormat imageFormat, CommandBuffer& buffer);

        void createVkImage(unsigned char* data, VulkanTexture* texture, VkDeviceSize imageSize);

        VkImageView createImageView(VulkanTexture* texture, VkFormat format, VkImageAspectFlags aspectFlags);

        void createTextureSampler(VulkanTexture* texture);

        void recreateSwapChain(uint32_t width, uint32_t height);

        VkPipelineLayout pipelineLayout;

        ExecuteQueues<std::function<void()>> executeQueues_Objects;

    public:
        enum class DescriptorLayoutType {
            Object,
            SimpleCamera,
            LightPoint,
            DirectionLight,
            Attachments
        };
        struct QueueFamilyIndices {
            
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;
            std::optional<uint32_t> transferFamily;
            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value() && transferFamily.has_value();
            }
        };

        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

        VulkanRender();

        ~VulkanRender();

    public:

        static VkDevice device;

        static VkPhysicalDevice physicalDevice;

        static VkInstance instance;

        static QueueFamilyIndices FamilyIndices;

    
    private:

        bool needCmdBuffersUpdate{ true };

        float totalTime;

        std::unique_ptr<VulkanRenderObjectFactory> factory;

        std::vector<std::shared_ptr<VulkanRenderObject>> objects;

        std::list<std::shared_ptr<VulkanPointLight>> lights;

        std::list<std::shared_ptr<VulkanCamera>> cameras;

        std::weak_ptr<VulkanDirLight> globalLight;

        VulkanWindow* window;

        VkPipeline graphicsPipeline;

        VkPipeline graphicsPipeline2;

        std::shared_ptr<RenderBuffer> cameraPlug;

        std::unique_ptr<DescriptorPool> VulkanRenderBufferPool;

        std::vector<std::unique_ptr<DescriptorPool>> renderObjectsPools;

        std::unique_ptr<DescriptorPool> cameraPool;

        std::unique_ptr<DescriptorPool> attachmentsSetPool;

        std::unique_ptr<DescriptorPool> lightPool;

        std::vector<std::unique_ptr<CommandPool>> concurrentCommandPools_RenderQueue;

        std::unique_ptr<CommandPool> swapChainRenderCommandPool;

        std::vector<std::unique_ptr<CommandPool>> concurrentCommandPools_TransferQueue;

        VkExtent2D currentRenderResolution;

        VkDescriptorSet setMainCamera;

        VkDescriptorSet globalLightSet;

        VkDescriptorSet pointLightsSet;

        std::vector<VkDescriptorSet> attachmentsSets;

        std::vector <std::unique_ptr<VulkanTexture>> normalAttachments;

        std::vector<std::unique_ptr<VulkanTexture>> colorAttachments;

        std::vector<std::unique_ptr<VulkanTexture>> depthAttachments;

        uint32_t MAX_COUNT_OF_OBJECTS = 10000;

        uint32_t MAX_COUNT_OF_LIGHTS = 1000;

        VkDebugUtilsMessengerEXT debugMessenger;

        VkSurfaceKHR surface;

        tbb::concurrent_queue<CommandBuffer> BufferRenderQueue;

        tbb::concurrent_queue<CommandBuffer> BufferTransferQueue;

        VkQueue graphicsQueue;

        VkQueue transferQueue;

        VkQueue presentQueue;

        VkSwapchainKHR swapChain;

        std::vector<VkImage> swapChainImages;

        VkFormat swapChainImageFormat;

        

        std::vector<VkImageView> swapChainImageViews;

        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;
        
        VkRenderPass resolutionScaling;

        std::map<DescriptorLayoutType, VkDescriptorSetLayout> layouts;

        VkDescriptorSetLayout ObjectWithoutTextureLayout;

        VkDescriptorSetLayout ObjectLayout;

        VkDescriptorSetLayout CameraLayout;

        VkDescriptorSetLayout LightLayout;

        std::unique_ptr<VulkanPipeline> pipeLine;
        
        VkCommandPool _commandPool;

        VkCommandBuffer _copyBuffer;

        std::vector<CommandBuffer> RenderBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;

        std::vector<VkSemaphore> renderFinishedSemaphores;

        std::vector<VkFence> inFlightFences;

        std::vector<VkFence> imagesInFlight;

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

        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

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

        void createObjectDescriptorSetLayout();

        void createLightDescriptorSetLayout();

        void createCameraDescriptorSetLayout();

        void createSyncObjects();

        void createCmdBuffers();

        void updateCmdBuffers();

        VkShaderModule createShaderModule(const std::vector<char>& code);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);


        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        bool isDeviceSuitable(VkPhysicalDevice device);

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        std::vector<const char*> getRequiredExtensions();

        bool checkValidationLayerSupport();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

        static std::vector<char> readFile(const std::string& filename);

        VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        const bool enableValidationLayers = true;

};
}