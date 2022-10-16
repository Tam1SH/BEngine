#include <tbb.h>
#include <functional>
export module ExecuteQueues;

namespace BEbraEngine {
	
	export enum class ExecuteType {
		Single,
		Multi
	};

	export template<typename Function>
	class ExecuteQueues {

	public:
		using Queue = tbb::concurrent_queue<Function>;


		void setStrategy(ExecuteType) { }

		void addTask(const Function& func) {
			parallelQueues[getCurrentThreadIndex()].push(func);
		}
		void addTask(ExecuteType type, Function&& func) {
			if (type == ExecuteType::Single)
				singleQueue.push(func);
			if (type == ExecuteType::Multi)
				parallelQueues[getCurrentThreadIndex()].push(func);
		}
		void reset() {
			for (auto& queue : parallelQueues) {
				queue.clear();
			}
		}

		template<typename... Args>
		void execute(Args&&... args) {

			auto f = [&](size_t i) {
				Function func;
				while (!parallelQueues[i].empty())
					if (parallelQueues[i].try_pop(func))
						func(std::forward<Args&&>(args)...);

			};

			tbb::parallel_for(
				tbb::blocked_range<size_t>(0, parallelQueues.size()),
					[&](size_t i) { f(i); });


			while (!singleQueue.empty()) {
				Function func;
				if (singleQueue.try_pop(func))
					func(std::forward<Args&&>(args)...);
			}
			
		}
		void execute() {

			auto f = [&](size_t i) {
				Function func;
				while (!parallelQueues[i].empty())
					if (parallelQueues[i].try_pop(func))
						func();

			};

			tbb::parallel_for<size_t>(
				0, parallelQueues.size(),
				[&](size_t i) { f(i); });
				
			while (!singleQueue.empty()) {
				Function func;
				if (singleQueue.try_pop(func))
					func();
			}

		}

		ExecuteQueues() {
			parallelQueues.resize(tbb::this_task_arena::max_concurrency());
		}


		ExecuteQueues(ExecuteQueues&& o) noexcept {
			Function f;
			singleQueue.clear();

			
		}

		ExecuteQueues& operator=(ExecuteQueues&& o) noexcept {

			Function f;
			singleQueue.clear();

			return *this;
		}

		ExecuteQueues(const ExecuteQueues&) noexcept = delete;
		ExecuteQueues& operator=(const ExecuteQueues&) noexcept = delete;

	private:
		int getCurrentThreadIndex()
		{

			int index = tbb::this_task_arena::current_thread_index();
			if (index >= tbb::this_task_arena::max_concurrency())
				index = 0;
			if (index < 0)
				index = 0;
			return index;
		}

	private:
		std::vector<Queue> parallelQueues;
		Queue singleQueue;
	};
}