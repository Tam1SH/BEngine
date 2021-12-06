#pragma once

#include "stdafx.h"
#include "AbstractRender.hpp"
#include "ExecuteQueues.hpp"
#undef min
#undef max



const int MAX_FRAMES_IN_FLIGHT = 3;

namespace BEbraEngine {
    class Texture;
    class Matrix4;
    class VulkanWindow;
    class Camera;
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
    class CommandBuffer;
    class VulkanDirLight;
    class VulkanPointLight;
    class VulkanRenderObjectFactory;
}

namespace std {
    template<typename T, typename D>
    class unique_ptr;
    template<class T>
    class shared_ptr;
}

namespace BEbraEngine {



    class VulkanRender : public AbstractRender
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

        void addCamera(std::shared_ptr<Camera> camera) override;

        void selectMainCamera(Camera* camera) override;

        void removeCamera(std::shared_ptr<Camera> camera) override;

        AbstractRender::Type getType() override { return AbstractRender::Type::Vulkan; }

        IRenderObjectFactory* getRenderObjectFactory() override;

        void addGlobalLight(std::shared_ptr<DirectionLight> globalLight) override;

        void drawFrame() override;

        uint32_t alignmentBuffer(uint32_t originalSize, AbstractRender::TypeBuffer type) override;

        VkDescriptorSet createDescriptor(VulkanDescriptorSetInfo* info);

        VkDescriptorSet createDescriptor(LightDescriptorInfo* info);

        VkDescriptorSet createDescriptor(RenderBuffer* buffer);

        void freeDescriptor(VulkanRenderObject* set);

        void freeDescriptor(VulkanDirLight* set);

        void freeDescriptor(VulkanPointLight* set);

        RenderBuffer* createBuffer(void* data, uint32_t size, VkBufferUsageFlags usage);

        void createVkImage(unsigned char* data, int texWidth, int texHeight, VkImage& textureImage, VkDeviceMemory& textureImageMemory, VkDeviceSize imageSize);

        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

        void createTextureSampler(VkSampler& textureSampler);

        void recreateSwapChain(uint32_t width, uint32_t height);

        VkPipelineLayout pipelineLayout;

        ExecuteQueues<std::function<void()>> executeQueues_Objects;

    public:
        enum class DescriptorLayoutType {
            Object,
            Camera,
            LightPoint,
            DirectionLight
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
        std::unique_ptr<VulkanRenderObjectFactory> factory;
        std::list<std::shared_ptr<VulkanRenderObject>> objects;
        std::list<std::shared_ptr<VulkanPointLight>> lights;
        std::list<std::shared_ptr<VulkanCamera>> cameras;

        std::weak_ptr<VulkanDirLight> globalLight;

        tbb::concurrent_queue<std::shared_ptr<VulkanRenderObject>> queueAddObject;
        tbb::concurrent_queue<std::shared_ptr<VulkanRenderObject>> queueDeleterObject;

        tbb::concurrent_queue<std::shared_ptr<VulkanPointLight>> queueAddLight;
        tbb::concurrent_queue<std::shared_ptr<VulkanPointLight>> queueDeleterLight;

        VulkanWindow* window;

        std::unique_ptr<DescriptorPool> VulkanRenderBufferPool;

        std::vector<std::unique_ptr<DescriptorPool>> renderObjectsPools;

        std::unique_ptr<DescriptorPool> cameraPool;

        std::unique_ptr<DescriptorPool> lightPool;

        std::vector<std::unique_ptr<CommandPool>> concurrentCommandPools_RenderQueue;

        std::vector<std::unique_ptr<CommandPool>> concurrentCommandPools_TransferQueue;


        VkDescriptorSet setMainCamera;

        uint32_t MAX_COUNT_OF_OBJECTS = 10000;

        uint32_t MAX_COUNT_OF_LIGHTS = 1000;

        VkDebugUtilsMessengerEXT debugMessenger;

        VkSurfaceKHR surface;

        tbb::concurrent_queue<CommandBuffer> BufferQueue;

        VkQueue graphicsQueue;

        VkQueue transferQueue;

        VkQueue presentQueue;

        VkSwapchainKHR swapChain;

        std::vector<VkImage> swapChainImages;

        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        std::vector<VkImageView> swapChainImageViews;

        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;

        std::map<DescriptorLayoutType, VkDescriptorSetLayout> layouts;

        VkDescriptorSetLayout ObjectWithoutTextureLayout;

        VkDescriptorSetLayout ObjectLayout;

        VkDescriptorSetLayout CameraLayout;

        VkDescriptorSetLayout LightLayout;


        VkPipeline graphicsPipeline;

        VkPipeline linegraphicsPipeline;

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

       

        VkQueue getGraphicsQueue();

        void addBufferToQueue(CommandBuffer buffer);

        VkFence* getCurrentFence();


        void recreateRenderObjects();

        void createDepthResources();

        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        VkFormat findDepthFormat();

        bool hasStencilComponent(VkFormat format);

       
        static void _createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        void copyBuffer1(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandBuffer& cmdBuffer);

        VkImageView createTextureImageView(VkImage& textureImage);

       
        
        //static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        VkDevice getDevice();

        static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandBuffer& buffer);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandBuffer& cmdbuffer);


       
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);


        void createInstance();

        void createPools();

        void cleanupSwapChain();

        void cleanUpDefault();

        void createAllDescriptorLayouts();

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        void setupDebugMessenger();

        void pickPhysicalDevice();

        void createLogicalDevice();

        void createSwapChain(uint32_t width, uint32_t height);

        void createImageViews();

        void createRenderPass();

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

        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

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
#ifdef _DEBUG
        const bool enableValidationLayers = true;
#else 
        const bool enableValidationLayers = false;
#endif

};
}