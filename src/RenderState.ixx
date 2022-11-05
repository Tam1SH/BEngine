module;
#include <variant>
#include <expected.hpp>
export module RenderState;
import <concepts>;
import Error;
import VulkanRenderState;
import CRenderState;

namespace BEbraEngine {

	template <typename RenderState, typename... RenderStates>
	struct _AreRenderStates : std::conditional_t<CRenderState<RenderState>, _AreRenderStates<RenderStates...>, std::false_type> {};
	template <typename RenderState>
	struct _AreRenderStates<RenderState> : std::bool_constant<CRenderState<RenderState>> {};

	export template <typename RenderState, typename... RenderStates>
		constexpr bool AreRenderStates = _AreRenderStates<RenderState, RenderStates...>::value;

	export template<typename...RenderStates>
		requires AreRenderStates<RenderStates...>
	struct _RenderState : std::variant<RenderStates...> {
		using Self = std::variant<RenderStates...>&;

		constexpr tl::expected<void, CreateStateError> create(const RenderStateCreateInfo& info) {
			return std::visit([](CRenderState auto& state) {
				return state.create(info);
			}, static_cast<Self>(*this));
		}

		constexpr void clear() {
			return std::visit([](CRenderState auto& state) {
				return state.clear();
			}, static_cast<Self>(*this));
		}

		_RenderState() {}
		template<typename RenderState>
		constexpr _RenderState(RenderState&& render) requires CRenderState<RenderState> {
			static_cast<Self>(*this) = std::forward<RenderState>(render);
		}

	};
	export using RenderState = _RenderState<VulkanRenderState>;
}