export module AllocationStrategy;
import <tuple>;
import <functional>;

namespace BEbraEngine {
	export enum struct EnumAllocationStrategy {
		High,
		Meddium,
		Low,
		AbsolutelyDontCare,
		throwOnAllocate,
		None,
	};

	export struct AllocationStrategy {

		static void setGlobalStrategy(EnumAllocationStrategy value) {
			AllocationStrategy::globalStrategy = value;
		}

		static EnumAllocationStrategy getGlobalStrategy() {
			return AllocationStrategy::globalStrategy;
		}

		AllocationStrategy() {
			currentStrategy = EnumAllocationStrategy::AbsolutelyDontCare;
		}

		void setStrategy(EnumAllocationStrategy value) {
			currentStrategy = value;
		}

		EnumAllocationStrategy getStrategy() {
			return currentStrategy;
		}

		virtual ~AllocationStrategy() = default;

		AllocationStrategy& operator=(const AllocationStrategy&) noexcept = default;
		AllocationStrategy(const AllocationStrategy&) noexcept = default;

		AllocationStrategy& operator=(AllocationStrategy&&) noexcept = default;
		AllocationStrategy(AllocationStrategy&&) noexcept = default;

	protected:

		template<typename ReturnType>
		using FuncPair = std::pair<EnumAllocationStrategy, std::function<ReturnType()>>;

		template<typename ReturnType = void>
		auto with(const std::initializer_list<FuncPair<ReturnType>>& list) {

			auto lolDontCare = FuncPair<ReturnType>(EnumAllocationStrategy::None, {});

			auto* strategy = std::find_if(list.begin(), list.end(), [&](FuncPair<ReturnType> pair) {
				if (pair.first == EnumAllocationStrategy::AbsolutelyDontCare)
					lolDontCare = pair;
				return pair.first == currentStrategy;
			});

			if (strategy != std::end(list))
				return strategy->second();
			else if (lolDontCare.first != EnumAllocationStrategy::None)
				return lolDontCare.second();

			return lolDontCare.second();
		}

	private:
		static inline EnumAllocationStrategy globalStrategy;
		EnumAllocationStrategy currentStrategy;
	};
}