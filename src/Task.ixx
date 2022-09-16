module;
#include <tbb.h>
#include <functional>
export module Task;
import <memory>;
import <stack>;

namespace BEbraEngine {
	export template<class T> 
	class Task {
	public:

		Task<T>& then(std::function<void(T&)>&& func) {
			onCompleted.push(func);
			return *this;
		}

		constexpr void failure(std::function<void()>&& func) {
			onFailure = func;
		}

		void execute(bool isSuccess) {
			if (isSuccess) {
				while (onCompleted.empty()) {
					auto val = onCompleted.top();
					val(*value);
					onCompleted.pop();
				}
			}
			else
				onFailure();
		}

		void setValue(T& value) {
		
			this->value.reset();
			this->value = std::shared_ptr<T>(&value);
		}

		constexpr Task() {}
		Task(T&& value) { this->value = std::shared_ptr<T>(value); }

		
		Task(const Task&) noexcept = default;
		Task& operator=(const Task&) noexcept = default;

	private:
		std::shared_ptr<T> value;
		std::stack<std::function<void(T&)>> onCompleted;
		std::function<void()> onFailure;
	};
}
