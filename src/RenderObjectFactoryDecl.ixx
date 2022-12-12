module;
#include <variant>
export module RenderObjectFactoryDecl;
import VulkanRenderObjectFactory;
import CRenderObjectFactory;


namespace BEbraEngine {
	export using RenderObjectFactory = std::variant<VulkanRenderObjectFactory>;
	static_assert(CRenderObjectFactory<VulkanRenderObjectFactory>);
}

