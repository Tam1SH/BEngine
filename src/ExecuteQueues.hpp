#pragma once
#include "stdafx.h"
namespace BEbraEngine {

	enum class ExecuteType {
		Single,
		Multi
	};
	template<typename Function>
	class ExecuteQueues {
	public:

	public:
		using Queue = tbb::concurrent_queue<Function>;


		void setStrategy(ExecuteType type) {
			this->type = type;
		}
		void addTask(Function&& func) {
			queues[getCurrentThreadIndex()].push(func);
		}

		template<typename... Args>
		void execute(Args&&... args) {
			auto f = [&](size_t i) {
				Function func;
				while (!queues[i].empty())
					if (queues[i].try_pop(func))
						func(std::forward<Args&&>(args));

			};

			if(type == ExecuteType::Multi)
				tbb::parallel_for(
					tbb::blocked_range<size_t>(0, queues.size()),
					[&](size_t i) 
					{ f(i); });

			if (type == ExecuteType::Single)
				for (int i = 0; i < queues.size(); i++)
					f(i);
			
		}
		void execute() {
			auto f = [&](size_t i) {
				Function func;
				while (!queues[i].empty())
					if (queues[i].try_pop(func))
						func();

			};

				if (type == ExecuteType::Multi)
					tbb::parallel_for<size_t>(
						0, queues.size(),
						[&](size_t i) { f(i); });

			if (type == ExecuteType::Single)
				for (int i = 0; i < queues.size(); i++)
					f(i);

		}
		ExecuteQueues() {
			queues.resize(tbb::this_task_arena::max_concurrency());
		}
	private:
		int getCurrentThreadIndex()
		{

			int index = tbb::this_task_arena::current_thread_index();
			if (index >= tbb::this_task_arena::max_concurrency())
				index = 0;

			return index;
		}

	private:
		std::vector<Queue> queues;
		ExecuteType type;
	};
}