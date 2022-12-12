#include "MethodDefineMacros.hpp"
#include <variant>
export module RenderAllocator;
import <concepts>;
import CRenderAllocator;
import VulkanRenderAllocator;
import Concepts;

namespace BEbraEngine {


	template<typename T>
	struct Concept : std::bool_constant<CRenderAllocator<T>> {};

	template <class...Ts>
	constexpr bool AreRenderAllocators = AreSuitableToBe<Concept, Ts...>;

	//Статически типизированный интерфейс для объектов, удовлетворяющими концепту CRenderAllocator<T> 
	export template<typename... RenderAllocators>
		requires AreRenderAllocators<RenderAllocators...>
	struct _RenderAllocator {

		METHOD_DEFINE_1(createIndexBuffer, CRenderAllocator, indices)
		METHOD_DEFINE_1(createVertexBuffer, CRenderAllocator, vertices)
		METHOD_DEFINE_1(createUniformBuffer, CRenderAllocator, size)
		METHOD_DEFINE_1(createStorageBuffer, CRenderAllocator, size)
		METHOD_DEFINE_2(alignmentBuffer, CRenderAllocator, originalSize, type)
		METHOD_DEFINE_1(destroyBuffer, CRenderAllocator, buffer)


		_RenderAllocator() {
			self = std::variant<RenderAllocators...>(std::in_place_index<0>);
		}

		template<typename RenderAllocator>
		RenderAllocator& get() {
			return std::get<RenderAllocator>(self);
		}

		std::variant<RenderAllocators...>& variant() {
			return self;
		}

		template<int index = 0>
		_RenderAllocator(std::in_place_index_t<index> i) {
			self = std::variant<RenderAllocators...>(i);
		}

		template<typename RenderAllocator>
		_RenderAllocator(RenderAllocator&& member) {
			//static_assert((std::is_same_v<RenderAllocator, RenderAllocators> && ...),
			//	"corresponds to the concept but does not correspond to the available types");
			this->self = std::forward<RenderAllocator>(member);
		}




	private:
		std::variant<RenderAllocators...> self;
	};
	
	export struct RenderAllocatorType {
		static constexpr auto Vulkan = std::in_place_index<0>;
	};

	export using RenderAllocator = _RenderAllocator<VulkanRenderAllocator>;

}
