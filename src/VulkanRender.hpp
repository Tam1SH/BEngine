#pragma once

#include "stdafx.h"
#include "stb_image.h"
#include <optional>
#include <stdexcept>
#include <array>
#include <fstream>
#include <set>
#include <oneapi/tbb.h>
#include <SDL_vulkan.h>
#include "Vertex.hpp"
#include "AbstractRenderSystem.hpp"
#include "CreateInfoStructures.hpp"
#include "VkBuffer.hpp"
#include "DescriptorSet.hpp"
#include "RenderObject.hpp"
#include "DescriptorPool.hpp"
#undef min
#undef max

const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = 1080;

#ifdef _DEBUG
    const bool enableValidationLayers = true;
#else 
    const bool enableValidationLayers = false;
#endif


const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAMES_IN_FLIGHT = 3;

const std::vector<BEbraEngine::Vertex> vertices = {

    
    
    {{-1,1,-1},{},{0.0f, 1.0f}},
    {{1,1,-1},{},{1.0f, 1.0f}},
    {{1,-1,-1},{},{1.0f, 0.0f}},
    {{-1,-1,-1},{},{0.0f, 0.0f}},
    {{-1,1,1},{},{1.0f, 0.0f}},
    {{1,1,1},{},{0.0f, 0.0f}},
    {{1,-1,1},{},{0.0f, 1.0f}},
    {{-1,-1,1},{},{1.0f, 1.0f}}
   
};

const std::vector<uint32_t> indices = {
  
    0, 1, 2,
    0, 2, 3,
    2, 1, 5,
    2, 5, 6,
    3, 2, 6,
    3, 6, 7,
    0, 3, 7,
    0, 7, 4,
    1, 0, 4,
    1, 4, 5,
    6, 5, 4,
    6, 4, 7
    
};
namespace BEbraEngine {
    class Texture;
    class Matrix4;
    class VulkanWindow;
    class Camera;
    //class Buffer;
    //class DescriptorSetLayouts;
}
//TODO: само существование всей этой хуйни является анти-оопешной блять. 
//Связанность с этим супер классом блять и всеми файлами которые трогают 
//рендер(почти все) настолько сильна, как связанность хронического алкоголика с бутылкой.
//Надо эту залупу переписывать нахуй под корень(хотя здесь нихуя и нет почти кроме инициализации).
namespace BEbraEngine {

    class VulkanRender : public AbstractRender
    {
    protected:
        std::unique_ptr<VulkanRenderObjectFactory> factory;
        std::list<std::weak_ptr<VulkanRenderObject>> objects;
        std::weak_ptr<VulkanLight> light;
    public:

        Camera* camera;
       
        void Create(BaseWindow* window) override;

        void DestroyBuffer(RenderBuffer* buffer) override;

        template<typename T>
        RenderBuffer* CreateBuffer(std::vector<T>& data, VkBufferUsageFlags usage);

        RenderBuffer* CreateUniformBuffer(size_t size) override;

        RenderBuffer* CreateStorageBuffer(size_t size);

        RenderBuffer* CreateIndexBuffer(std::vector<uint32_t> indices) override;

        RenderBuffer* CreateVertexBuffer(std::vector<Vertex> vertices) override;

        void AddObject(std::weak_ptr<RenderObject> object) override;

        void addLight(std::weak_ptr<Light> light) override;

        void InitCamera(Camera* alloced_camera) override;

        AbstractRender::Type getType() override { return AbstractRender::Type::Vulkan; }

        IRenderObjectFactory* getRenderObjectFactory() override { return factory.get(); }

        VkDescriptorSet createDescriptor(VulkanDescriptorSetInfo* info);

        VkDescriptorSet createDescriptor(LightDescriptorInfo* info);

        void createDescriptor(RenderBuffer* buffer);

        void freeDescriptor(VkDescriptorSet set);

    public:
        enum class DescriptorLayout {
            ObjectLayout,
            CameraLayout,
            LightLayout
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

    public:
        VulkanWindow* window;

        VkDescriptorSet objectTransforms;

        VkDescriptorSet setMainCamera;

        size_t COUNT_OF_OBJECTS = 0;

        size_t MAX_COUNT_OF_OBJECTS = 5000;

        VkDebugUtilsMessengerEXT debugMessenger;

        VkSurfaceKHR surface;

        tbb::concurrent_queue<VkCommandBuffer> BufferQueue;

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

        VkDescriptorPool descriptorPool;

        std::unique_ptr<DescriptorPool> RenderObjectPool;

        std::unique_ptr<DescriptorPool> cameraPool;

        std::unique_ptr<DescriptorPool> lightPool;

        std::map<DescriptorLayout, VkDescriptorSetLayout> layouts;

        VkDescriptorSetLayout ObjectWithoutTextureLayout;

        VkDescriptorSetLayout ObjectLayout;

        VkDescriptorSetLayout CameraLayout;

        VkDescriptorSetLayout LightLayout;

        VkPipelineLayout pipelineLayout;

        VkPipeline graphicsPipeline;

        VkPipeline linegraphicsPipeline;

        VkCommandPool commandPool;

        VkCommandBuffer _copyBuffer;

        std::vector<VkCommandBuffer> RenderBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;

        std::vector<VkSemaphore> renderFinishedSemaphores;

        std::vector<VkFence> inFlightFences;

        std::vector<VkFence> imagesInFlight;

        VkPhysicalDeviceProperties GPU_properties;


        size_t currentFrame = 0;

        bool isCreate;

        bool framebufferResized = false;

        bool IsCreate();

        VkQueue GetGraphicsQueue();

        static VulkanBuffer CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage);

        void AddBufferToQueue(VkCommandBuffer buffer);

        VkFence* GetCurrentFence();

        void recreateSwapChain(uint32_t width, uint32_t height);

        void recreateRenderObjects();

        void createDepthResources();

        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        VkFormat findDepthFormat();

        bool hasStencilComponent(VkFormat format);

        void ResizeDescriptorPool(unsigned int count);

        size_t pad_uniform_buffer_size(size_t originalSize);

        static void _createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        void copyBuffer1(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandBuffer& cmdBuffer);

        VkImageView createTextureImageView(VkImage& textureImage);

        VkImage createTextureImage(const std::string& path, VkDeviceMemory& textureImageMemory);

        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

        void createTextureSampler(VkSampler& textureSampler);

        //static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        VkDevice GetDevice();

        static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandBuffer& buffer);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandBuffer& cmdbuffer);


        void createVkImage1();

        void createVkImage2(stbi_uc* pixels, int texWidth, int texHeight, VkImage& textureImage, VkDeviceMemory& textureImageMemory, VkCommandBuffer& buffer);

        void createVkImage(stbi_uc* pixels, int texWidth, int texHeight, VkImage& textureImage, VkDeviceMemory& textureImageMemory, VkDeviceSize imageSize, VkBuffer& stagingBuffer);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        static VkCommandPool CreateCommandPool();

        VkCommandBuffer createCmdBuffer();

        static VkCommandBuffer createCmdBuffer(VkCommandPool pool);

        void UpdateFrame();

        void createInstance();
    private:

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

        void createDescriptorPool();

        void createObjectDescriptorSetLayout();

        void createLightDescriptorSetLayout();

        void createCameraDescriptorSetLayout();

        void createSyncObjects();

     //   VkCommandBuffer beginSingleTimeCommands();

      //  void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        void createCmdBuffers();

        void createCopyCmdBuffer();

        void UpdateCmdBuffers();

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

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
        static void WriteDataOnBuffer(VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size);
};


    template<typename T>
    inline RenderBuffer* VulkanRender::CreateBuffer(std::vector<T>& data, VkBufferUsageFlags usage)
    {
        VulkanBuffer* buffer = new VulkanBuffer();
        VkDeviceSize bufferSize = sizeof(data[0]) * data.size();
        buffer->size = bufferSize;
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        _createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* _data;
        vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &_data);
        memcpy(_data, data.data(), (size_t)bufferSize);
        vkUnmapMemory(device, stagingBufferMemory);

        _createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer->self, buffer->memory);
        copyBuffer(stagingBuffer, buffer->self, bufferSize);

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);

        return buffer;
    }
}