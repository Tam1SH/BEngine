module;
#include "MethodDefineMacros.hpp"
export module RenderObjectFactory;
import VulkanRenderObjectFactory;
import CRenderObjectFactory;
import Concepts;
import <concepts>;
import <variant>;


namespace BEbraEngine {


	template<typename T>
	struct Concept : std::bool_constant<CRenderObjectFactory<T>> {};

	template <class...Ts>
	constexpr bool AreRenderObjectFactories = AreSuitableToBe<Concept, Ts...>;

	//Статически типизированный интерфейс для объектов, удовлетворяющими концепту CRenderObjectFactory<T> 
	export template<typename... RenderObjectFactories>
		requires AreRenderObjectFactories<RenderObjectFactories...>
	struct _RenderObjectFactory {

		METHOD_DEFINE_2(createMaterialAsync, CRenderObjectFactory, obj, material)
		METHOD_DEFINE_1(create, CRenderObjectFactory, renderInfo)
		METHOD_DEFINE_2(bindTransform, CRenderObjectFactory, obj, trans)
		METHOD_DEFINE_2(createLight, CRenderObjectFactory, color, position)
		METHOD_DEFINE_2(createDirLight, CRenderObjectFactory, color, direction)
		METHOD_DEFINE_1(createCamera, CRenderObjectFactory, position)
		METHOD_DEFINE_1(destroyObject, CRenderObjectFactory, object)
		METHOD_DEFINE_1(destroyCamera, CRenderObjectFactory, camera)
		METHOD_DEFINE_2(setModel, CRenderObjectFactory, object, path)
		METHOD_DEFINE_1(destroyPointLight, CRenderObjectFactory, light)
		

		_RenderObjectFactory() {
			self = std::variant<RenderObjectFactories...>(std::in_place_index<0>);
		}

		template<typename RenderObjectFactory>
		RenderObjectFactory& get() {
			return std::get<RenderObjectFactory>(self);
		}

		std::variant<RenderObjectFactories...>& variant() {
			return self;
		}

		template<int index = 0>
		_RenderObjectFactory(std::in_place_index_t<index> i) {
			self = std::variant<RenderObjectFactories...>(i);
		}

		template<typename RenderObjectFactory>
		_RenderObjectFactory(RenderObjectFactory&& member) {
			//static_assert((std::is_same_v<RenderAllocator, RenderAllocators> && ...),
			//	"corresponds to the concept but does not correspond to the available types");
			this->self = std::forward<RenderObjectFactory>(member);
		}

	private:
		std::variant<RenderObjectFactories...> self;
	};

	export struct RenderObjectFactoryType {
		static constexpr auto Vulkan = std::in_place_index<0>;
	};

	export using RenderObjectFactory = _RenderObjectFactory<VulkanRenderObjectFactory>;
	static_assert(CRenderObjectFactory<VulkanRenderObjectFactory>);
}


