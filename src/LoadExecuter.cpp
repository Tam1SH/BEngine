#include "LoadExecuter.hpp"
#undef min
namespace BEbraEngine {
    
    void LoadExecuter::Create(VkDevice& device, BaseVulkanRender* render)
    {
        this->render = render;
        CommandBuffer::SetDevice(device);
        this->device = device;
        CommandBuffer::SetRender(render);
        _pool = render->CreateCommandPool();
        
        maxTasks = taskPool.max_concurrency() / 2;
    }

    void LoadExecuter::AddToQueue(Task func)
    {
        tasks.push(func);
        totalTasks++;
    }

    void LoadExecuter::OnCompletedAll(Callback func)
    {
        _OnCompletedAll = func;
    }

    void LoadExecuter::OnCompletedPart(Callback func)
    {
        _OnCompletedPart = func;
    }

    void LoadExecuter::WriteAllBuffers()
    {
        if (!tasks.empty()) {
            int count = std::min(totalTasks, maxTasks);
            for (int i = 0; i < count; i++) {
                CommandBuffer buffer;
                buffer.SetPool(render->CreateCommandPool());
                buffer.Create();
                ExecuteBuffers.push(buffer);

            }
            while (!ExecuteBuffers.empty()) {
                if (Task req; tasks.try_pop(req)) {
                    CommandBuffer cmdBuffer;
                    ExecuteBuffers.try_pop(cmdBuffer);

                    taskPool.enqueue([this, cmdBuffer, req]() {

                        auto& buffer = const_cast<CommandBuffer&>(cmdBuffer);
                        buffer.StartRecord();
                        req(buffer);
                        buffer.EndRecord();
                        RecordedBuffers.push(buffer);

                        taskCompleted.fetch_add(1);
                        if (AllTasksCompleted())
                            ExecuteAll();
                        });

                }
                else {

                }
            }

        }
        else {
            if (_OnCompletedAll)
                _OnCompletedAll();
            //Я не ебу как отследить завершение работы буфферов, по этому перемещаю их в очередь "завершённых" 
            // TODO 
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            while (!RecordedBuffers.empty()) {

                CommandBuffer buffer;
                RecordedBuffers.try_pop(buffer);
                VkCommandBuffer& buf = buffer;
                vkFreeCommandBuffers(device, buffer.GetPool(), 1, &buf);
                vkDestroyCommandPool(device, buffer.GetPool(), 0);

            }
        }

    }

    bool LoadExecuter::AllTasksCompleted()
    {
        bool b1 = taskCompleted == maxTasks;
        bool b2 = taskCompleted == totalTasks;
        if (b1 || b2)
            return true;
        return false;
    }

    void LoadExecuter::ExecuteAll()
    {
        std::lock_guard g(m);
        std::vector<VkCommandBuffer> completedBuffers;
        int count = RecordedBuffers.unsafe_size();
        for (int i = 0; i < count; i++) {
            CommandBuffer buf;
            RecordedBuffers.try_pop(buf);
            completedBuffers.push_back(buf);
            RecordedBuffers.push(buf);
        }

        for (auto& buffer : completedBuffers) {
            render->AddBufferToQueue(buffer);
        }

        totalTasks -= taskCompleted;
        taskCompleted = 0;

        if (totalTasks > 0 && _OnCompletedPart)
            _OnCompletedPart();
        WriteAllBuffers();




        //});
    }

    VkCommandBuffer LoadExecuter::CreateBuffer()
    {
        VkCommandBuffer buffer;
        VkCommandBufferAllocateInfo info{};
        info.commandBufferCount = 1;
        info.commandPool = _pool;
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        if (auto result = vkAllocateCommandBuffers(device, &info, &buffer);
            result != VK_SUCCESS) {

        }
        return buffer;

    }
    
}
