#pragma once

#include "C:\.BEbraEngine\Include\stb-master\stb_image.h"
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <optional>
#include <stdexcept>
#include <array>
#include <glm/glm.hpp>
#include <fstream>
#include "Image.hpp"
#include "VkBuffer.hpp"
#include <set>
#include <oneapi/tbb.h>
#include "DescriptorSetLayouts.hpp"
#include <SDL_vulkan.h>
#include "Vertex.h"
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

const std::vector<Vertex> vertices = {

    
    
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

    class __vulkanRender {
    private:
        VkDevice device;
        VkPhysicalDevice physicalDevice;
        VkInstance instance;

        std::optional<VkQueue> graphicsQueue;
        std::optional<VkQueue> transferQueue;
        std::optional<VkQueue> presentQueue;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;

        std::vector<VkSemaphore> imageAvailableSemaphores;

        std::vector<VkSemaphore> renderFinishedSemaphores;

        std::vector<VkFence> inFlightFences;

        std::vector<VkFence> imagesInFlight;

        VkPhysicalDeviceProperties GPU_properties;

        VkRenderPass renderPass;



    };

    class VulkanWindow;
    class BaseVulkanRender
    {

    public:
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

        BaseVulkanRender();

        virtual ~BaseVulkanRender();

    public:

        static VkDevice device;

        static VkPhysicalDevice physicalDevice;

        static VkInstance instance;

        static QueueFamilyIndices FamilyIndices;

    public:
        VulkanWindow* window;


        size_t COUNT_OF_OBJECTS = 0;

        size_t MAX_COUNT_OF_OBJECTS = 5000;

        DescriptorSetLayouts DescriptorLayouts;

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

        VkDescriptorSetLayout ObjectWithoutTextureLayout;

        VkDescriptorSetLayout ObjectLayout;

        VkDescriptorSetLayout CameraLayout;

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

        virtual void Init() = 0;

        virtual void OnCleanUp() = 0;

        virtual void OnRecreateSwapChain() = 0;

        virtual void OnDrawFrame() = 0;

        virtual void OnUpdateData() = 0;

        virtual void SetDescriptorLayouts() = 0;

        static Buffer CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage);

        void AddBufferToQueue(VkCommandBuffer buffer);

        VkFence* GetCurrentFence();

        void recreateSwapChain();

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

        void initRender();

    private:




        void cleanupSwapChain();

        void cleanUpDefault();


        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        void setupDebugMessenger();

        void pickPhysicalDevice();

        void createLogicalDevice();

        void createSwapChain();

        void createImageViews();

        void createRenderPass();

        void createGraphicsPipeline();

        void createLineGraphicsPipeline();

        void createFramebuffers();

        void createCommandPool();

        void createDescriptorPool();

        void createObjectDescriptorSetLayout();

        void createObjectWithoutTextureLayout();

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
    };
}