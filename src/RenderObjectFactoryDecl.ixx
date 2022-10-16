module;
#include <variant>
#include <boost\filesystem.hpp>

export module RenderObjectFactoryDecl;
import VulkanRenderObjectFactory;

namespace BEbraEngine {
	export using RenderObjectFactory = std::variant<VulkanRenderObjectFactory>;
}

