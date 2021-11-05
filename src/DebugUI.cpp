#include "stdafx.h"

#ifdef __ANDROID__1
#include "DebugUI.h"
namespace BEbraEngine {
    
    void DebugUI::check_vk_result(VkResult err)

    {
        if (err == 0)
            return;
        fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
        if (err < 0)
            abort();
    }

    void DebugUI::_createPool()
    {
        VkDescriptorPoolSize pool_sizes[] =
        {
            { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        };
        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
        pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
        pool_info.pPoolSizes = pool_sizes;
        VkResult err = vkCreateDescriptorPool(VulkanRender::device, &pool_info, 0, &imguiPool);
        check_vk_result(err);
    }

    void DebugUI::UploadFonts()
    {

        // Use any command queue
        VkCommandPool command_pool = VulkanRender::CreateCommandPool();
        VkCommandBuffer command_buffer = VulkanRender::createCmdBuffer(command_pool);

        VkResult err = vkResetCommandPool(VulkanRender::device, command_pool, 0);
        check_vk_result(err);
        VkCommandBufferBeginInfo begin_info = {};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(command_buffer, &begin_info);
        check_vk_result(err);

        ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

        VkSubmitInfo end_info = {};
        end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        end_info.commandBufferCount = 1;
        end_info.pCommandBuffers = &command_buffer;
        err = vkEndCommandBuffer(command_buffer);
        check_vk_result(err);
        err = vkQueueSubmit(render->graphicsQueue, 1, &end_info, VK_NULL_HANDLE);
        check_vk_result(err);

        err = vkDeviceWaitIdle(VulkanRender::device);
        check_vk_result(err);
        ImGui_ImplVulkan_DestroyFontUploadObjects();
        vkFreeCommandBuffers(VulkanRender::device, command_pool, 1, &command_buffer);
        vkDestroyCommandPool(VulkanRender::device, command_pool, 0);

    }

    void DebugUI::Create(VulkanRender* render, VulkanWindow* window)
    {
        _createPool();
        this->render = render;
        this->window = window;
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForVulkan(window->GetHandle());
        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = render->instance;
        init_info.PhysicalDevice = render->physicalDevice;
        init_info.Device = render->device;
        init_info.QueueFamily = render->FamilyIndices.graphicsFamily.value();
        init_info.Queue = render->graphicsQueue;
        init_info.PipelineCache = 0;
        init_info.DescriptorPool = imguiPool;
        init_info.Allocator = 0;
        init_info.MinImageCount = 2;
        init_info.ImageCount = 8;
        init_info.CheckVkResultFn = check_vk_result;
        ImGui_ImplVulkan_Init(&init_info, render->renderPass);

        UploadFonts();
    }

    void DebugUI::SetWorkSpace(std::shared_ptr<WorkSpace> workspace)
    {
        this->workspace = workspace;
    }

    GameObjectComponent* selected;

    void DebugUI::TreeObjects(std::shared_ptr<GameObjectComponent> component) {
        static int i;

        static int selection_mask = (1 << 2);
        int node_clicked = -1;

        if (!component->IsComposite()) {
            return;
        }



        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

        ImGuiTreeNodeFlags node_flags = base_flags;
        const bool is_selected = (selection_mask & (1 << (i))) != 0;
        if (is_selected)
            node_flags |= ImGuiTreeNodeFlags_Selected;

        bool isOpen = false;//ImGui::TreeNodeEx((void*)(intptr_t)(i), node_flags, component->GetName().c_str());

        if (ImGui::IsItemClicked()) {
            if (component->GetName() != "Workspace") {
                node_clicked = i;
                std::cout << component->GetName() << std::endl;
                selected = component.get();
            }

        }

        if (isOpen && ImGui::IsItemClicked())
        {
            for (auto _component : component->Components) {
                TreeObjects(_component);
            }

            ImGui::TreePop();
               

        }


        if (node_clicked != -1)
        {
            // Update selection state
            // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
            if (ImGui::GetIO().KeyCtrl)
                selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
            else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                selection_mask = (1 << node_clicked);           // Click to single-select
        }



        i = (i + 1) % (workspace->GetSize() + 1);

    }
    void DebugUI::Prepare()
    {
        // Start the Dear ImGui frame
        if (workspace.get()) {

            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplSDL2_NewFrame(window->GetHandle());
            ImGui::NewFrame();
            bool show_demo_window = true;
            bool show_another_window = false;
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::SetNextWindowPos(ImVec2(0, 0));
                auto size = ImGui::GetIO().DisplaySize;
                ImGui::SetNextWindowSize(ImVec2(size.x / 5.0f, size.y));
                ImGui::Begin("Tree", 0, ImGuiWindowFlags_NoResize
                    | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
                // Create a window called "Hello, world!" and append into it.
                TreeObjects(workspace);


                //  ImGui::tre
                ImGui::End();


                ImGui::SetNextWindowPos(ImVec2(size.x - size.x / 5.0f, 0));

                ImGui::SetNextWindowSize(ImVec2(size.x / 5.0f, size.y));
                if (selected) {
                    ImGui::Begin(selected->GetName().c_str(), 0, ImGuiWindowFlags_NoResize
                        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

                    ImGui::End();
                }

            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            // Rendering
            ImGui::Render();
        }
    }

    void DebugUI::Destroy()
    {
        vkDestroyDescriptorPool(VulkanRender::device, imguiPool, 0);
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
    
}

#endif