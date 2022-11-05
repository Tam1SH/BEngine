module;
#include <expected.hpp>

export module CRenderState;
import <concepts>;
import Error;

namespace BEbraEngine {

	export struct RenderStateCreateInfo {};

	export template<typename State>
		concept CRenderState = requires(State& self, const RenderStateCreateInfo& info)
	{
		{ self.create(info) } -> std::same_as<tl::expected<void, CreateStateError>>;
		{ self.clear()      } -> std::same_as<void>;
	};
}