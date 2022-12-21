module;
export module Task;
import <functional>;
import <memory>;
import <stack>;
//TODO: есть ли смысл от велосипеда? Думаю нет.
namespace BEbraEngine {
	export template<class T> 
	struct Task {

		Task<T>& then(std::function<void(T&)>&& func) {
			onCompleted.push(func);
			return *this;
		}

		constexpr void failure(std::function<void()>&& func) {
			onFailure = func;
		}

		void execute(T&& value, bool isSuccess) const {
			//TODO: думаю надо хотя бы лок какой-нибудь сделать чтобы подождать появление хотя бы какой-нибудь задачи,
			// либо сделать какой-нибудь submit
			if (isSuccess) {
				auto _onCompleted = onCompleted;

				while (!_onCompleted.empty()) {
					_onCompleted.top()(value);
					_onCompleted.pop();
				}
			}
			else
				onFailure();
		}

		constexpr Task() {}

		Task(const Task&) noexcept = default;
		Task& operator=(const Task&) noexcept = default;

	private:
		std::stack<std::function<void(T&)>> onCompleted;
		std::function<void()> onFailure;
	};
}
