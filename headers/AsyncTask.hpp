
namespace BEbraEngine {
	template<typename Action, typename OnCompleted = void, typename OnCancel = void>
	class AsyncTask {
	public:
		template<typename Args&&...>
		void run(Args&&... args) {
			action(args);
		}

	protected:
		Action action{};
		OnCompleted completed{};
		OnCancel cancel{};
	};
}