#pragma once
#include "stdafx.h"
#include <functional>
#include "CommandBuffer.hpp"
#include "VulkanRender.hpp"
namespace BEbraEngine {
    /*
    
    class VulkanAsyncExecuter {
    public:

        typedef std::function<void(CommandBuffer&)> Task;

        typedef std::function<void()> Callback;
    public:

        VulkanAsyncExecuter() { }

        void Create(VkDevice& device, VulkanRender* render);

        void AddToQueue(Task func);

        void OnCompletedAll(Callback func);

        void OnCompletedPart(Callback func);

        void WriteAllBuffers();

    private:

        bool AllTasksCompleted();

        void ExecuteAll();

        VkCommandBuffer createBuffer();

    private:
        std::mutex m;

        int maxTasks;
        int totalTasks;
        std::atomic<int> taskCompleted;

        VkDevice device;
        VkCommandPool _pool;

        tbb::concurrent_queue<CommandBuffer> RecordedBuffers;
        tbb::concurrent_queue<CommandBuffer> ExecuteBuffers;
        tbb::concurrent_queue<Task> tasks;

        tbb::task_arena taskPool;

        VulkanRender* render;

        Callback _OnCompletedAll;
        Callback _OnCompletedPart;
    };
    */
    

}