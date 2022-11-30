module;
#include <variant>

export module RenderObjectFactoryDecl;
import VulkanRenderObjectFactory;

namespace BEbraEngine {
	export using RenderObjectFactory = std::variant<VulkanRenderObjectFactory>;
}

