module;
#include <tbb.h>
#include <vulkan.h>
#include <optional>
#include <memory>
#include <mutex>
#include <map>
#include <vector>
#include <functional>
#include <string>
#include "CommandBuffer.hpp"
export module VulkanRender;
import Render;
import ExecuteQueues;
import RenderData;
import RenderAllocatorTypeRenderBuffer;
import RenderHelper;
import Vector2;
import VulkanPipeline;
import LineShaderData;
import Vertex;
import VulkanRenderBufferArray;
import CommandPool;
import DescriptorPool;
class btIDrawDebug;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::function;
using std::optional;
using std::map;
using std::list;
using std::string;
using std::atomic;


namespace BEbraEngine {
    export struct RenderBuffer;
    export struct VulkanWindow;
    export struct VulkanDirLight;
    export struct VulkanPointLight;
    export struct VulkanCamera;
    export struct VulkanRenderObject;
    export struct VulkanTexture;
    export struct Texture;
    export struct LightDescriptorInfo;
    export struct VulkanDescriptorSetInfo;
    export struct Vector3;
    export struct LolCompileErrorXD;
}


namespace BEbraEngine {

    export struct VulkanRender : public Render
    {
        
        void update() override;

        void prepareDraw() override;

        void drawFrame() override;

        void updateState(RenderData& data) override;

        void create(VulkanWindow& window);
        
        void destroyBuffer(RenderBuffer* buffer);

        RenderBuffer* createUniformBuffer(uint32_t size);

        RenderBuffer* createStorageBuffer(uint32_t size);

        RenderBuffer* createIndexBuffer(vector<uint32_t> indices);

        RenderBuffer* createVertexBuffer(vector<Vertex> vertices);
        
        void drawLine(const Vector3& from, const Vector3& to, const Vector3& color);

        
        Vector2 getCurrentRenderResolution();

        uint32_t alignmentBuffer(uint32_t originalSize, TypeRenderBuffer type);

        VkDescriptorSet createDescriptor(const VulkanDescriptorSetInfo& info);

        void updateDesriptor(VkDescriptorSet& set, VulkanDescriptorSetInfo* info);

        VkDescriptorSet createDescriptor(LightDescriptorInfo* info);

        VkDescriptorSet createDescriptor2(RenderBufferView* buffer);

        VkDescriptorSet createDescriptor(RenderBuffer* buffer);
        
        void freeDescriptor(VulkanRenderObject& set);

        void freeDescriptor(VulkanDirLight* set);

        void freeDescriptor(VulkanPointLight* set);

        void destroyTextureAsync(shared_ptr<VulkanTexture> texture);

        RenderBuffer* createBufferAsync(void* data, uint32_t size, VkBufferUsageFlags usage);

        void generateMipmaps(VulkanTexture* texture, VkFormat imageFormat, CommandBuffer& buffer);

        void createVkImage(unsigned char* data, VulkanTexture* texture, VkDeviceSize imageSize);

        VkImageView createImageView(VulkanTexture* texture, VkFormat format, VkImageAspectFlags aspectFlags);

        void createTextureSampler(VulkanTexture* texture);
        
        VulkanTexture* getBitMapFromSwapChainImage();

        void recreateSwapChain(uint32_t width, uint32_t height);

        VulkanRender() {}
        VulkanRender(const VulkanRender&) noexcept {}
        VulkanRender& operator=(const VulkanRender&) noexcept { return *this; }
        //VulkanRender(VulkanRender&&) noexcept = default;
        //VulkanRender& operator=(VulkanRender&&) noexcept = default;

        ~VulkanRender();
        

    public:
        enum struct DescriptorLayoutType {
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
        
    public:

        static VkDevice device;

        static VkPhysicalDevice physicalDevice;

        static VkInstance instance;

        static QueueFamilyIndices FamilyIndices;

    
    private:
        
        bool isCreated{};
        
        VkPipelineLayout pipelineLayout;

        ExecuteQueues<function<void()>> executeQueues;


        std::mutex m;

        bool needCmdBuffersUpdate{ true };

        float totalTime;

        tbb::concurrent_queue<CommandBuffer> BufferRenderQueue;

        tbb::concurrent_queue<CommandBuffer> BufferTransferQueue;

        RenderData currentData;

        VkDescriptorSet lineSet;

        atomic<size_t> linesToDraw{0};

        atomic<size_t> linesToDrawLastUpdate;

        vector<CommandBuffer> buffersToDestroy;

        VkDescriptorSet objectSet;

        vector<LineShaderData> linesMemory{ 30000 };

        unique_ptr<VulkanRenderBufferArray<LineShaderData>> linePool;

        list<VulkanCamera*> cameras;

        VulkanDirLight* globalLight;
        
        
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
        
        LolCompileErrorXD* t;

        VkExtent2D currentRenderResolution;

        VkDescriptorSet setMainCamera;

        VkDescriptorSet globalLightSet;

        VkDescriptorSet pointLightsSet;

        VkDescriptorSet physicsDebugSet;
        
        
        vector<VkDescriptorSet> attachmentsSets;

        vector<shared_ptr<VulkanTexture>> normalAttachments;

        vector<shared_ptr<VulkanTexture>> colorAttachments;

        vector<shared_ptr<VulkanTexture>> depthAttachments;

        uint32_t MAX_COUNT_OF_OBJECTS = 1000;

        uint32_t MAX_COUNT_OF_LIGHTS = 100;

        VkDebugUtilsMessengerEXT debugMessenger;

        VkSurfaceKHR surface;

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


        void createDepthResources();

        VkFormat findSupportedFormat(const vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        VkFormat findDepthFormat();

        bool hasStencilComponent(VkFormat format);

        static void _createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        void copyBuffer1(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandBuffer& cmdBuffer);

        VkDevice getDevice();

        static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createImage(VulkanTexture* texture, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);

        void transitionImageLayout(VulkanTexture* texture, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandBuffer& buffer);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandBuffer& cmdbuffer);
       
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        void createInstance(VulkanWindow& window);

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